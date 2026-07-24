/**
 * @file ScheduleManager.h
 * @brief Provides the top-level facade for coordinating schedules, registries, and persistence services.
 * @author Melia Kek Xin Hui
 */
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

/**
 * @brief High-level coordinator that wires registries, persistence, and matching workflows together.
 * @author Melia Kek Xin Hui
 */
class ScheduleManager {
private:
    PassengerList passengerRegistry{};
    ShuttleList shuttleRegistry{};
    SystemDataService dataService{};
    SchedulingService schedulingService{};

public:
    LoadResult loadAllSystemData(const string& folder = "");

    PassengerList& getPassengerRegistry();
    ShuttleList& getShuttleRegistry();
    const PassengerList& getPassengerRegistry() const;
    const ShuttleList& getShuttleRegistry() const;

    /**
     * @brief Returns all entities as a polymorphic view through the shared Entity interface.
     * @return Collection of entity pointers that can be handled uniformly at runtime.
     */
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
