#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Passenger.h"
#include "ShuttleVehicle.h"
using namespace std;

// Purpose: Small immutable value object representing one matched passenger-shuttle
// pairing. Does not own the Passenger/ShuttleVehicle it points to; ownership stays
// with the registries in ScheduleManager.
class Schedule {
private:
    const Passenger* assignPassenger;
    const ShuttleVehicle* assignShuttle;

public:
    Schedule(const Passenger* passenger, const ShuttleVehicle* shuttle);
    Schedule(const Schedule& other);
    Schedule& operator=(const Schedule& other);
    ~Schedule() = default;

    const Passenger* getPassenger() const;
    const ShuttleVehicle* getShuttle() const;
};

#endif
