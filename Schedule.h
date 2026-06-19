#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Passenger.h"
#include "ShuttleVehicle.h"
#include "Registry.h"
#include <vector>
#include <string>
using namespace std;

class PassengerList : public Registry<Passenger> {};
class ShuttleList : public Registry<ShuttleVehicle> {};

class Schedule {
private:
    const Passenger* assignPassenger;
    const ShuttleVehicle* assignShuttle;

public:
    Schedule(const Passenger* passenger, const ShuttleVehicle* shuttle);

    const Passenger* getPassenger() const;
    const ShuttleVehicle* getShuttle() const;
    Schedule(const Schedule&) = default;
    Schedule& operator=(const Schedule&) = default;
};

class ScheduleList {
private:
    ShuttleList shuttleRegistry;
    PassengerList passengerRegistry;
    vector<Schedule> activeSchedules;

public:
    ScheduleList() = default;

    PassengerList& getPassengerRegistry();
    ShuttleList& getShuttleRegistry();
    const vector<Schedule>& getActiveSchedules() const;

    void generateSchedules();
    void clearSchedules();
};

#endif
