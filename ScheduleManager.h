#ifndef SCHEDULE_MANAGER_H
#define SCHEDULE_MANAGER_H

#include "Registry.h"
#include "SystemDataService.h"
#include "SchedulingService.h"
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Entity;

// Purpose: Top-level application service. Replaces the former ScheduleList
// god-class: instead of one class owning the registries, persistence, AND the
// matching algorithm, each concern now lives in its own class (SystemDataService,
// ScheduleMatcher, ScheduleRepository via SchedulingService) and ScheduleManager
// simply wires them together (Facade Pattern) for the UI layer to use.
class ScheduleManager {
private:
    PassengerList passengerRegistry;
    ShuttleList shuttleRegistry;
    SystemDataService dataService;
    SchedulingService schedulingService;

public:
    bool loadAllSystemData(const string& folder = "");

    PassengerList& getPassengerRegistry();
    ShuttleList& getShuttleRegistry();
    const PassengerList& getPassengerRegistry() const;
    const ShuttleList& getShuttleRegistry() const;

    // Genuinely polymorphic view: Passenger and ShuttleVehicle objects are exposed
    // here only through their shared Entity interface. A caller iterating this
    // vector cannot tell (and does not need to know) which concrete type each
    // element is - getDescription()/getType()/isValid() dispatch to the correct
    // override at runtime for each element.
    vector<const Entity*> getAllEntities() const;

    void setMatchingStrategy(unique_ptr<IMatchingStrategy> strategy);
    string getStrategyName() const;
    void runMatchingAlgorithm();
    const vector<Schedule>& getSchedules() const;
    void clearSchedules();

    bool savePassengerData(const string& path) const;
    bool saveShuttleData(const string& path) const;
    bool editPassenger(const string& id, const string& newDestination, const string& newTime, int newGroupSize);
    bool editShuttle(const string& id, const string& newDestination, const string& newTime, const string& newModel);
};

#endif
