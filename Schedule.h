#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Passenger.h"
#include "ShuttleVehicle.h"
#include "Registry.h"
#include <vector>

class PassengerList : public Registry<Passenger> {};
class ShuttleList : public Registry<ShuttleVehicle> {};

class Schedule {
private:
    Passenger* assignPassenger;
    ShuttleVehicle* assignShuttle;

public:
    Schedule(Passenger* passenger, ShuttleVehicle* shuttle, bool assigned);
    Schedule(const Schedule& other);
    Schedule& operator=(const Schedule& other);
    ~Schedule() = default;

    const Passenger* getPassenger() const;
    const ShuttleVehicle* getShuttle() const;
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
};

#endif