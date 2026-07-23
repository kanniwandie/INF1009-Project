# INF1009 Project - Route Planner

This README is the source of truth for the project structure, build instructions, and module layout.

## Purpose

A C++ console application for a driverless shuttle Route-Planner. It loads passenger
and shuttle data from text files, supports RAM-only Add/Edit/Delete of both, computes
matched schedules using one of two selectable dispatch algorithms, and exports
schedules and data to new text files on request.

## Project Structure

```text
INF1009/
├── main.cpp
│
├── MenuController.h / .cpp          # UI layer: console menus, delegates to ScheduleManager
├── UserInputParser.h / .cpp         # Wraps PassengerParser/ShuttleParser for menu-typed input
│
├── ScheduleManager.h / .cpp         # Application facade: owns registries + services
├── SchedulingService.h / .cpp       # Facade over ScheduleMatcher + ScheduleRepository
├── ScheduleMatcher.h / .cpp         # Runs a pluggable IMatchingStrategy
├── ScheduleRepository.h / .cpp      # Stores the currently computed schedules
├── Schedule.h / .cpp                # Value object: one Passenger-Shuttle pairing
├── IMatchingStrategy.h / .cpp       # Strategy interface + MinimumDispatchStrategy / EarliestArrivalStrategy
│
├── SystemDataService.h / .cpp       # Coordinates load/edit/save of passenger & shuttle data
├── FileLoader.h / .cpp              # Abstract loader + PassengerParser / ShuttleParser
├── DataExporter.h / .cpp            # Writes passenger/shuttle data back to new text files
├── ScheduleOutputHandler.h / .cpp   # Strategy interface + ConsolePrinter / TextFileFormatter
│
├── Registry.h / .cpp                # Generic ID-keyed store; PassengerList/ShuttleList compose it
├── Entity.h / .cpp                  # Abstract base: id, destination, time, assigned status, isValid()
├── DriverlessVehicle.h / .cpp       # Abstract intermediate layer between Entity and ShuttleVehicle
├── Passenger.h / .cpp
├── ShuttleVehicle.h / .cpp
├── ShuttleModel.h / .cpp            # Small / Family / Premium capacity + naming strategy
│
├── Time.h / .cpp                    # Abstract time base
├── OperationalTime.h / .cpp         # Concrete Time: parses "H:MMam/pm", enforces 6am-midnight
├── TimeFormatter.h                  # Formatting interface
├── AMPMTimeFormatter.h / .cpp
├── ISOTimeFormatter.h / .cpp
│
├── Destination.h / .cpp             # Value object (replaces raw string destinations)
├── PassengerID.h / .cpp             # Value object (replaces raw string passenger IDs)
├── VehicleID.h / .cpp               # Value object (replaces raw string vehicle IDs)
│
├── passenger.txt
├── shuttle.txt
│
├── README.md                        # This file
├── BREAKDOWN.md                     # Design/architecture discussion
├── CHANGE_SUMMARY.md                # Log of fixes made since the Part 1 feedback
├── evidence/                        # Proof the two algorithms genuinely differ + complexity write-up
└── UML.mermaid                      # Class diagram source (paste into mermaid.live to export PDF)
```

## Build

```bash
g++ -std=c++17 -o app *.cpp
```

## Run

```bash
./app
```
(On Windows: `app.exe` or `.\app.exe`)

Press Enter at the folder prompt to load `passenger.txt`/`shuttle.txt` from the current
directory, or type a different folder path.

## Notes

- Layered structure: UI (`MenuController`) → application facade (`ScheduleManager`) →
  domain services (`SchedulingService`, `SystemDataService`) → domain entities
  (`Entity`/`Passenger`/`ShuttleVehicle`) and infrastructure (`FileLoader`,
  `DataExporter`, `ScheduleOutputHandler`).
- Matching is implemented via the Strategy Pattern (`IMatchingStrategy`), letting the
  user pick Minimum Dispatch or Earliest Arrival at runtime — the two produce
  genuinely different schedules; see `evidence/` for a worked example proving it.
- Output rendering (console vs. file) is also Strategy-based (`ScheduleOutputHandler`).
- `ScheduleManager::getAllEntities()` + `ScheduleOutputHandler::writeEntityOverview()`
  demonstrate genuine polymorphism: Passengers and ShuttleVehicles are iterated as a
  single mixed `vector<const Entity*>`, dispatched through the base interface only.
- For what changed since the Part 1 feedback and why, see `CHANGE_SUMMARY.md`.
- For the architecture/SOLID/design-pattern discussion, see `BREAKDOWN.md`.