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
    string passengerID;
    string shuttleID;
    string destination;
    string scheduledTime;

public:
    Schedule(const string& pID, const string& sID,
             const string& dest, const string& time);

    const string& getPassengerID() const;
    const string& getShuttleID() const;
    const string& getDestination() const;
    const string& getScheduledTime() const;
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
