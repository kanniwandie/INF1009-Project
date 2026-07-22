# Design Breakdown – Part 2 Implementation

## 1. Architecture and design principles

The current implementation has been reworked to follow a more layered and maintainable structure. The main goal was to separate business-domain logic from UI and infrastructure concerns so the system is easier to extend and test.

### What has been done
- The project now uses a layered structure:
  - Domain layer: entities such as Passenger, ShuttleVehicle, Time, OperationalTime, Destination, and shuttle models.
  - Service/application layer: ScheduleList, SystemDataService, and persistence helpers.
  - UI/infrastructure layer: MenuController, UserInputParser, FileLoader, and output handlers.
- This separation improves clarity and reduces direct coupling between the console interface and the business logic.

### What to improve
- A more formal dependency injection mechanism could be introduced so services receive their dependencies explicitly instead of constructing them internally.
- The UI layer could be further reduced so menu logic focuses only on user interaction and leaves even more behaviour in services.

## 2. SOLID principles and maintainability

### What has been done
- Single Responsibility Principle (SRP): each class is focused on a single concern such as parsing, matching, rendering, or storage.
- Open/Closed Principle (OCP): the matching system can be extended by adding new strategy classes without changing the core scheduling engine.
- Dependency Inversion Principle (DIP): higher-level components depend on abstractions such as IMatchingStrategy and ScheduleOutputHandler rather than on concrete implementations.

### What to improve
- The code would benefit from more explicit interfaces and dependency injection to make testing easier and reduce hidden coupling.
- Some formatting and validation logic is still somewhat embedded in the UI and output layers, which could be further extracted into reusable helpers.

## 3. Design patterns implemented

### Strategy Pattern
The matching behaviour is implemented using the Strategy Pattern.

### What has been done
- IMatchingStrategy defines a common interface for matching behaviour.
- MinimumDispatchStrategy and EarliestArrivalStrategy implement different matching rules.
- ScheduleList uses the strategy object dynamically, so the matching logic can be swapped easily.

### Why this is useful
- The scheduling engine can support different policies without changing its core structure.
- This makes the design more scalable and reusable.

### What to improve
- The current strategy selection is still fairly simple. A more advanced configuration layer could allow the user to choose strategies through a more flexible menu or configuration file.

### Adapter / Facade Pattern
The input and service layers also reflect adapter/facade-style design.

### What has been done
- UserInputParser adapts raw input from the menu into the parser layer.
- SystemDataService acts as a façade that coordinates loading, editing, saving, and archive creation.

### What to improve
- These layers could be made even more cohesive by introducing clearer abstractions for persistence and data access.

## 4. Layered architecture

### What has been done
- The business logic for matching and schedule generation is separated from the console UI.
- The UI layer now focuses on reading user input and displaying output.
- Parser and formatter layers are isolated so data can be processed consistently from files, console input, or saved archives.

### Why this helps
- Business logic can be tested without depending on the UI.
- The system is easier to evolve if new input or output channels are introduced later.

### What to improve
- A stronger separation between application services and domain entities would make the architecture even cleaner.
- More test coverage across the service layer would further validate the design.

## 5. Summary

### Completed
- Refactored the system around a layered architecture.
- Added strategy-based matching.
- Introduced abstraction for output rendering.
- Improved data handling and persistence behaviour.
- Added a Mermaid UML for the current implementation.

### Remaining improvements
- Add automated unit tests.
- Improve dependency injection and configuration flexibility.
- Reduce duplicated formatting logic.
- Expand parser validation and input handling for more complex user input.
