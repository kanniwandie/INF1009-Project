# Change Summary

## Part 2 Fixes (round 6 - exhaustive input testing)

Testing deliberately malformed inputs (empty files, garbage CSV rows, non-numeric
fields, duplicate IDs, bad prompt input) surfaced several real, previously-undetected
bugs:

- **Silent data corruption (the serious one).** `OperationalTime::parse()` fell back
  to `(6, 0)` - a fully *valid*-looking time - whenever it failed to parse a garbage
  time string. Same for group size: a non-numeric field silently became `1`. Both
  meant corrupted data in a file would load as a plausible, "Valid" entity with no
  indication anything was wrong, and could have silently entered a real schedule.
  Fixed by using an unambiguous sentinel (`hour = -1`, `groupSize = -1`) that fails
  validation instead of a plausible default.
- **`Passenger::isValid()` didn't catch it either**, because it deliberately skips
  the shuttle-only 6am-midnight operating-hours check (needed for the legitimate
  post-midnight arrival case from the spec). Added a narrower check - "was this time
  parsed at all" (`getHour() >= 0`) - that catches genuinely unparseable input without
  reintroducing the operating-hours restriction on passengers.
- **Malformed/duplicate rows in data files vanished silently** with zero feedback.
  `Registry<T>::add()` now returns `bool` (was `void`), and `PassengerParser`/
  `ShuttleParser::load()` print a `[Warning]` line with the file, line number, and
  raw content for every row that's skipped (missing fields) or rejected (duplicate ID).
- **Input-stream desync bug**: typing non-numeric text (e.g. "abc") at a Group Size
  prompt left `cin` in a fail state with the bad token still in the buffer, which then
  silently corrupted the *next* prompt's read (a menu selection would be consumed by
  the leftover garbage instead of read fresh). Fixed by explicitly checking `cin.fail()`
  and clearing/discarding the bad line immediately after every numeric extraction.
- Verified empty data files and a nonexistent data folder both fail gracefully with a
  clear message rather than crashing.

## Part 2 Fixes (round 5)

- **Fixed an infinite loop on EOF.** `MenuController::getMenuChoice()` would loop
  forever printing "Invalid input" if the input stream ever ran dry (Ctrl+D, a piped
  script ending, redirected input from a file that's shorter than expected). `cin.clear()`
  resets the failbit but doesn't un-exhaust an actually-ended stream, so the retry loop
  never succeeded and never terminated. Now detects `cin.eof()` and exits cleanly with
  a message instead of hanging.

## Part 2 Fixes (round 4 - spec compliance audit)

- **Requirement 10 was completely missing from the menu.** `ScheduleManager::save
  PassengerData()`/`saveShuttleData()` existed and worked, but no menu option ever
  called them - there was no way for the user to actually save passenger/shuttle data
  to new files. Added menu option 7, "Save Passenger/Shuttle Data to New Files."
- **Found and fixed a round-trip data corruption bug** while testing the above:
  `DataExporter::saveShuttles()` was writing `getName()` ("Small Shuttle") instead of
  the raw token the file format and parser expect ("Small"). Any exported shuttle file
  would silently reload with every shuttle defaulting to Small on the next load - the
  exact bug from round 1, just reintroduced via a different code path. Fixed by adding
  `ShuttleModel::getCode()` (the raw file-format token) as distinct from `getName()`
  (the human-readable display label), and pointing the exporter at the former. Verified
  round-trip: exported real shuttle data, reloaded it, confirmed Premium/Family/Small
  models all survive intact.

## Part 2 Fixes (round 3)

- **Entry-level validation added to all four CRUD paths** (Add Passenger, Add Shuttle,
  Edit Passenger, Edit Shuttle) in `MenuController::handleDataManagementMenu()`. Group
  size (1-15), destination non-empty, and shuttle model (Small/Family/Premium exactly)
  are now checked before the entry is accepted, with a specific error message per
  failure. Previously an unrecognized model string (e.g. "Deluxe") silently defaulted
  to `SmallShuttleModel` with no warning; that's now rejected explicitly. Edits are
  rolled back to the pre-edit value if the result fails `isValid()`.
- **Evidence package added under `evidence/`**: a deliberately constructed dataset
  (`evidence/divergence_demo/`) proves Minimum Dispatch and Earliest Arrival choose
  different shuttles for the identical passenger/data, plus saved archive output from
  both strategies. `evidence/ALGORITHM_EVIDENCE_AND_COMPLEXITY.md` has the write-up and
  a full time-complexity derivation for both strategies, ready to drop into the report.

## Part 2 Fixes (round 2)

- **Genuine polymorphism added.** `Entity::isValid()` is now a real part of the base
  interface (pure virtual), not something bolted onto `Passenger`/`ShuttleVehicle`
  separately. More importantly, `ScheduleManager::getAllEntities()` builds an actual
  `vector<const Entity*>` mixing Passengers and ShuttleVehicles together, and
  `ScheduleOutputHandler::writeEntityOverview()` (implemented in both `ConsolePrinter`
  and `TextFileFormatter`) loops over that single mixed collection calling
  `getType()`/`isValid()`/`getDescription()` through the base pointer - the concrete
  type is never checked or known at the call site, it's resolved by virtual dispatch.
  Wired into "Display All Data" so it's visible during the demo.
- **Registry composition instead of inheritance.** `PassengerList`/`ShuttleList` now
  compose a `Registry<T>` as a private member (HAS-A) instead of inheriting from it
  (IS-A), matching the original Part 1 feedback. `Registry<T>` stays fully generic and
  domain-agnostic; the domain-specific classes forward to it. No call sites elsewhere
  in the codebase needed to change - the public API is identical.

## Part 2 Fixes (round 1)

- **Fixed a correctness bug**: `MinimumDispatchStrategy` and `EarliestArrivalStrategy`
  previously ran identical logic, so both "algorithms" produced the same schedule. They
  now implement genuinely different global policies: Minimum Dispatch sorts shuttles by
  capacity (largest first) and packs each one before moving on; Earliest Arrival picks,
  per passenger, whichever eligible shuttle arrives soonest. Verified against the spec's
  own worked examples.
- **Added the missing menu option** to actually choose between the two strategies at
  runtime - previously `ScheduleList` (now `ScheduleManager`) always ran the default
  strategy and there was no way to switch.
- **Fixed a data-loading bug**: the CRLF line endings in `passenger.txt`/`shuttle.txt`
  left a trailing `\r` on the last field of every row. `trim()` didn't strip it, so every
  shuttle model comparison silently failed and fell back to `SmallShuttleModel`
  regardless of what the file said. Fixed by stripping `\r`/`\n` in `trim()`.
- **Fixed a midnight-rollover bug** in the 10-minute arrival window check: a shuttle at
  11:59pm and a passenger requesting 12:05am should be treated as 6 minutes apart, not
  rejected as being ~24 hours apart. Now uses circular time-of-day arithmetic.
- **Broke up the `ScheduleList` god-class** into `Schedule` (value object),
  `ScheduleRepository` (storage), `ScheduleMatcher` (runs a strategy),
  `SchedulingService` (facade over the two), and `ScheduleManager` (top-level facade
  owning the registries + `SystemDataService` + `SchedulingService`).
- **Removed dead/duplicate code**: `SchedulePrinter` and `ScheduleStorage` were static
  utility classes left over from before the `ScheduleOutputHandler`/`ConsolePrinter`/
  `TextFileFormatter` refactor, but `main.cpp` was still wired to the old ones. Deleted
  both and switched all console/file output through `ScheduleOutputHandler`.
- **Made `MenuController` instance-based** rather than a fully-static utility class; it
  now holds a `ScheduleManager&` and delegates all business logic to it.
- Redrew `UML.mermaid` to match the actual class structure above (the previous diagram
  described classes - `ScheduleManager`, `ScheduleMatcher`, etc. - that didn't exist yet
  in the code).

## What changed since the previous implementation

This document records the main changes introduced in the current iteration of the project.

### Architecture and structure
- Refactored the project into a more layered design.
- Separated domain objects, services, input parsing, and output rendering into distinct responsibilities.
- Reduced direct coupling between the console menu and the core business logic.

### Scheduling and matching
- Introduced a strategy-based matching approach for schedule generation.
- Added support for multiple matching strategies through the IMatchingStrategy abstraction.
- The schedule engine can now evaluate candidate matches using a more extensible rule structure.

### Input and data handling
- Added parsing support for file-based input and menu-based input.
- Improved passenger and shuttle handling to include group size, shuttle model, and assignment tracking.
- Added service-layer edit operations for updating passengers and shuttles.

### Output and persistence
- Introduced a dedicated output abstraction for rendering schedules to the console and files.
- Added a schedule archive writer so computed schedules can be saved in a readable format.
- Improved the formatting of schedule output for clarity.

### Design quality improvements
- Improved modularity and maintainability by grouping related responsibilities into focused classes.
- Made the design easier to extend by introducing abstractions for matching and output rendering.
- Improved alignment with layered architecture and software design principles such as SOLID.
