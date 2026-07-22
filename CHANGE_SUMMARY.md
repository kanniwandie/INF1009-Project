# Change Summary

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
