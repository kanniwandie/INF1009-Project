# INF1009 Project

## File Structure

```
Project/
├── Entity.h / Entity.cpp                 Base class with id, destination, scheduledTime
├── Passenger.h / Passenger.cpp           Passenger entity with assignment status
├── DriverlessVehicle.h / DriverlessVehicle.cpp   Base vehicle entity
├── ShuttleVehicle.h / ShuttleVehicle.cpp         Shuttle entity with assignment status
├── Registry.h                            Template class for managing collections
├── Schedule.h / Schedule.cpp             Schedule (matched pair) and ScheduleList (orchestrator)
├── SchedulePrinter.h / SchedulePrinter.cpp   Console output for schedules and entities
├── ScheduleStorage.h / ScheduleStorage.cpp   File I/O for saving schedules
├── MenuController.h / MenuController.cpp UI, data loading, input validation, CRUD
├── main.cpp                              Entry point
├── passenger.txt                         Sample passenger data
├── shuttle.txt                           Sample shuttle data
└── README.md
```

## Build

```bash
g++ -std=c++17 *.cpp -o route_planner
```

## Class Hierarchy

```
Entity (abstract)
├── Passenger
└── DriverlessVehicle
    └── ShuttleVehicle

Registry<T>
├── PassengerList = Registry<Passenger>
└── ShuttleList   = Registry<ShuttleVehicle>

Schedule          (stores pointers to matched Passenger/Shuttle)
ScheduleList      (owns registries + schedules)
SchedulePrinter   (static display methods)
ScheduleStorage   (static file save methods)
MenuController    (static UI methods)
```
