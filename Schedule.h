#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Passenger.h"
#include "ShuttleVehicle.h"
#include "Registry.h"
#include "IMatchingStrategy.h"
#include <memory>
#include <vector>
#include <string>
using namespace std;

class Schedule {
private:
    const Passenger* assignPassenger;
    const ShuttleVehicle* assignShuttle;

public:
    Schedule(const Passenger* passenger, const ShuttleVehicle* shuttle);
    // Copy Constructor
    Schedule(const Schedule& other);
    // Copy Assignment Operator
    Schedule& operator=(const Schedule& other);
    // Destructor, Doesn't own the lifecycle of the pointers, default is okay
    ~Schedule() = default;
    const Passenger* getPassenger() const;
    const ShuttleVehicle* getShuttle() const;
};

class ScheduleList {
private:
    ShuttleList shuttleRegistry;
    PassengerList passengerRegistry;
    vector<Schedule> activeSchedules;
    unique_ptr<IMatchingStrategy> matchingStrategy;

public:
    ScheduleList();

    PassengerList& getPassengerRegistry();
    ShuttleList& getShuttleRegistry();
    const vector<Schedule>& getActiveSchedules() const;

    void setMatchingStrategy(unique_ptr<IMatchingStrategy> strategy);
    void generateSchedules();
    void clearSchedules();
};

#endif
