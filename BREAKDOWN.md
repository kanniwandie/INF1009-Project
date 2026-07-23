# Design Breakdown – Part 2 Implementation

## 1. Architecture and design principles

The system is layered to separate UI, application orchestration, domain logic, and
infrastructure concerns.

- **UI layer**: `MenuController` — reads console input, delegates every piece of
  actual work to `ScheduleManager`. Contains no parsing, matching, or persistence
  logic itself.
- **Application facade layer**: `ScheduleManager` — owns the passenger/shuttle
  registries plus `SystemDataService` and `SchedulingService`, and exposes one simple
  interface for the UI to call.
- **Domain/service layer**: `SchedulingService` (facade over `ScheduleMatcher` +
  `ScheduleRepository`), `SystemDataService` (load/edit/save orchestration).
- **Domain entities**: `Entity` (abstract) → `Passenger`, and `Entity` →
  `DriverlessVehicle` → `ShuttleVehicle`; value objects `Destination`, `PassengerID`,
  `VehicleID`, `Time`/`OperationalTime` replace primitive strings/ints for these
  fields.
- **Infrastructure**: `FileLoader`/`PassengerParser`/`ShuttleParser` (reading),
  `DataExporter` (writing), `ScheduleOutputHandler`/`ConsolePrinter`/
  `TextFileFormatter` (rendering).

### What to improve

- No formal dependency-injection container — services are constructed as members
  rather than injected. For a project this size that's a reasonable trade-off, but
  it's worth naming as a deliberate scope decision rather than an oversight.
- `MenuController` still reads `std::cin` directly rather than through an input
  abstraction, so it isn't unit-testable in isolation without real console input.

## 2. SOLID principles

Assessed honestly against the actual classes, not just in the abstract.

### Single Responsibility

Holds for most of the codebase — `ScheduleRepository`, `ScheduleMatcher`,
`Destination`/`PassengerID`/`VehicleID`, and the `IMatchingStrategy`/
`ScheduleOutputHandler` implementations each do exactly one thing.

Two honest exceptions:
- `ScheduleManager` combines four concerns (registry ownership, delegating to
  persistence, delegating to matching, exposing entities). Defensible as a Facade,
  but it's the class most at risk of growing back into a god-class if the system
  expands further.
- `MenuController::handleDataManagementMenu()` is one large method handling six
  distinct CRUD operations in a single switch statement. It delegates the actual
  work correctly, but the menu-flow logic for six operations still lives in one place.

### Open/Closed

- `IMatchingStrategy` and `ScheduleOutputHandler` are genuinely open for extension:
  a new dispatch algorithm or a new output format can be added without modifying any
  existing class (`ScheduleMatcher`, `SchedulingService`, `ScheduleManager`,
  `MenuController` are all untouched by such an addition).
- `ShuttleModel` creation in `FileLoader.cpp` is **not** open/closed — adding a new
  shuttle model means editing an `if/else` chain of string comparisons. A factory
  keyed by name (e.g. a `map<string, function<unique_ptr<ShuttleModel>()>>`) would
  fix this; it currently doesn't exist.

### Liskov Substitution

Holds, and is directly demonstrated in code: `ScheduleOutputHandler::
writeEntityOverview()` iterates a `vector<const Entity*>` containing both `Passenger`
and `ShuttleVehicle` objects with zero type-checking or special-casing — every call
(`getType()`, `isValid()`, `getDescription()`) dispatches correctly regardless of
which concrete type is behind the pointer.

### Interface Segregation

No major violations — every method on `IMatchingStrategy` and `ScheduleOutputHandler`
is used meaningfully by every implementer. One soft spot: read-only consumers of
`PassengerList`/`ShuttleList` (like the output classes) are handed the same fully
mutable interface as CRUD code; a stricter design would expose a const, iteration-only
view to the former.

### Dependency Inversion

Real in one place, not fully applied in another:
- `ScheduleMatcher` depends only on the `IMatchingStrategy` abstraction — genuine DIP.
- `MenuController` does **not** fully apply DIP to output rendering: it constructs
  `ConsolePrinter`/`TextFileFormatter` directly inline rather than depending on
  `ScheduleOutputHandler` via injection. The abstraction exists and is used
  polymorphically once constructed, but `MenuController` is still compile-time coupled
  to the concrete classes.

## 3. Design patterns implemented

### Strategy Pattern (used twice, independently)

1. **Matching algorithms** — `IMatchingStrategy`, implemented by
   `MinimumDispatchStrategy` (packs the highest-capacity eligible shuttle first, to
   minimize the number of shuttles dispatched) and `EarliestArrivalStrategy` (picks,
   per passenger, whichever eligible shuttle arrives soonest). `ScheduleMatcher` holds
   an `IMatchingStrategy` and never knows which concrete strategy it's running.
   Verified with a constructed dataset (one passenger, two eligible shuttles of
   different capacity/arrival time) that the two strategies produce different,
   individually-correct schedules from identical input.
2. **Output rendering** — `ScheduleOutputHandler`, implemented by `ConsolePrinter`
   (writes to `stdout`) and `TextFileFormatter` (writes to a file). Same interface,
   swappable at the call site.

### Facade Pattern

`ScheduleManager` (and, inside it, `SchedulingService`) hides the registries,
persistence, matching engine, and schedule storage behind one simple interface for
`MenuController` to call, so the UI layer never needs to know about `ScheduleMatcher`,
`ScheduleRepository`, or `SystemDataService` directly.

*(Earlier drafts of this document described `UserInputParser` as an Adapter. On
review that's not accurate — it doesn't convert between incompatible interfaces, it's
a thin pass-through reusing `PassengerParser`/`ShuttleParser` for menu-typed input.
Corrected here rather than left as an over-claim.)*

## 4. Polymorphism

Part 1 feedback specifically noted that polymorphism existed technically but
contributed little to actual behaviour, since collections were always accessed
through their concrete types. This has been addressed directly:

- `Entity::isValid()` is now part of the base interface (pure virtual), not something
  `Passenger` and `ShuttleVehicle` each happen to define independently.
- `ScheduleManager::getAllEntities()` returns a genuinely mixed
  `vector<const Entity*>` containing both Passengers and ShuttleVehicles.
- `ScheduleOutputHandler::writeEntityOverview()` loops over that single mixed
  collection once, calling `getType()`/`isValid()`/`getDescription()` purely through
  the base pointer — the concrete type is never checked, only resolved by the vtable
  at runtime.

The matching engine (`MinimumDispatchStrategy`/`EarliestArrivalStrategy`)
deliberately still uses the typed `PassengerList`/`ShuttleList` registries rather than
`vector<Entity*>`. Both algorithms genuinely need type-specific data
(`getGroupSize()`, `getMaxSeats()`) that isn't on the shared `Entity` interface;
forcing that data through downcasting would be polymorphism in name only, and would
make the matching code worse, not better.

## 5. Data modelling (fixing primitive obsession)

Part 1 feedback noted heavy reliance on raw `string`/`int` fields for domain concepts.
`Destination`, `PassengerID`, `VehicleID`, and `Time`/`OperationalTime` are now real
value objects with their own validation (`isValid()`), centralizing what used to be
scattered string/number checks and giving each concept a single place to change if
its rules change.

`PassengerList`/`ShuttleList` compose a `Registry<T>` rather than inheriting from it
(previously `class ShuttleList : public Registry<ShuttleVehicle> {}`), addressing the
specific Part 1 note that "PassengerList uses a Registry" is a more accurate model
than "PassengerList is a Registry."

## 6. Round 7 hardening

Further work beyond the initial round of fixes, focused on input robustness:

- Time parsing rewritten to use `std::regex` with a strict format
  (`^(\d{1,2}):(\d{2})\s*([aApP][mM])$`), rejecting more malformed input than the
  original manual-parsing approach did.
- Shuttle model matching made case-insensitive (`normalizeModel()`), applied
  consistently at both file-load time and interactive menu input.
- Group size parsing tightened to require the entire field be numeric, rather than
  accepting a numeric prefix (e.g. "5abc" no longer silently becomes 5).
- File parsers now validate an entity (`isValid()`) *before* inserting it into a
  registry, rather than inserting unconditionally and relying on downstream code to
  notice it's invalid. This is a deliberate design shift from the previous approach:
  invalid rows are now fully excluded rather than visible-but-flagged.
- `ScheduleManager::clearSchedules()` now resets both registries' assignment flags,
  not just the schedule repository — fixes a staleness bug where entities stayed
  marked "Assigned" after their computed schedule was cleared.
- Requirement 10's "never overwrite existing files" rule is now enforced at two
  independent layers: `MenuController` and `DataExporter` each check
  `std::filesystem::exists()` before writing.
- Schedule archive timestamps now use platform-appropriate thread-safe calls
  (`localtime_s`/`localtime_r`) instead of the non-thread-safe `localtime()`.

## 7. Summary

### Completed this iteration
- Fixed the two matching algorithms so they genuinely differ (previously identical).
- Broke up the `ScheduleList` god-class into four single-purpose classes.
- Added real polymorphism via `getAllEntities()` / `writeEntityOverview()`.
- Switched `Registry` composition instead of inheritance.
- Fixed several data-integrity bugs: CRLF corruption silently defaulting every
  shuttle to "Small," garbage input being silently coerced into valid-looking
  defaults instead of failing visibly, and a save/reload round-trip bug.
- Added entry-level input validation and load-time warnings for malformed data.
- Corrected the UML diagram and this document to match the code, rather than
  describing an aspirational design.
- (Round 7) Hardened input parsing, closed a schedule-clearing staleness bug, and
  double-enforced the no-overwrite rule for saved data files.

### Remaining, acknowledged limitations
- No automated test suite — verification in this round was manual/exploratory,
  not exhaustive.
- `ShuttleModel` construction violates OCP (string-matched if/else chain).
- `MenuController` still couples directly to `cin` and to concrete `ConsolePrinter`/
  `TextFileFormatter` rather than depending on injected abstractions.
- No dependency-injection mechanism; services are owned as members, not injected.