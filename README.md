# INF1009 Project

This README is the source of truth for the project structure, build instructions, and the main module layout.

## Purpose

This project is a C++ console application for managing passengers, shuttles, and schedule generation. It supports loading data from text files, editing records, generating matched schedules, and exporting results.

## Project Structure

```text
INF1009/
├── main.cpp
├── MenuController.h / MenuController.cpp
├── SystemDataService.h / SystemDataService.cpp
├── UserInputParser.h / UserInputParser.cpp
├── FileLoader.h / FileLoader.cpp
├── Schedule.h / Schedule.cpp
├── SchedulePrinter.h / SchedulePrinter.cpp
├── ScheduleOutputHandler.h / ScheduleOutputHandler.cpp
├── ScheduleStorage.h / ScheduleStorage.cpp
├── DataExporter.h / DataExporter.cpp
├── Registry.h
├── Entity.h / Entity.cpp
├── DriverlessVehicle.h / DriverlessVehicle.cpp
├── Passenger.h / Passenger.cpp
├── ShuttleVehicle.h / ShuttleVehicle.cpp
├── ShuttleModel.h / ShuttleModel.cpp
├── Time.h / Time.cpp
├── OperationalTime.cpp / OperationalTime.h
├── TimeFormatter.h
├── AMPMTimeFormatter.h / AMPMTimeFormatter.cpp
├── ISOTimeFormatter.h / ISOTimeFormatter.cpp
├── IMatchingStrategy.h / IMatchingStrategy.cpp
├── Destination.h / Destination.cpp
├── PassengerID.h / PassengerID.cpp
├── VehicleID.h / VehicleID.cpp
├── passenger.txt
├── shuttle.txt
├── test1.txt
├── test2.txt
├── README.md
├── BREAKDOWN.md
├── UMLPhase2.mermaid
└── CHANGE_SUMMARY.md
```

## Build

Run the following command from the project folder:

```bash
g++ -std=c++17*.cpp -o route_planner
```

## Run
```bash
./app.exe
```

## Notes

- The system uses a layered structure with separate concerns for UI, services, parsers, domain objects, and output formatting.
- Matching behaviour is implemented using a strategy-based design.
- For a detailed summary of what changed since the previous implementation, see CHANGE_SUMMARY.md.
- For the design breakdown and architectural discussion, see BREAKDOWN.md.

