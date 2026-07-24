/**
 * @file ScheduleManager.cpp
 * @brief Implements the facade that coordinates schedules, registries, and persistence services.
 * @author Melia Kek Xin Hui
 */
#include "ScheduleManager.h"
#include "Passenger.h"
#include "ShuttleVehicle.h"
#include <utility>
using namespace std;

LoadResult ScheduleManager::loadAllSystemData(const string& folder) {
    // Clear any previous in-memory state before loading a fresh dataset from disk.
    passengerRegistry.clear();
    shuttleRegistry.clear();
    return SystemDataService::loadInitialData(passengerRegistry, shuttleRegistry, folder);
}

PassengerList& ScheduleManager::getPassengerRegistry() { return passengerRegistry; }
ShuttleList& ScheduleManager::getShuttleRegistry() { return shuttleRegistry; }
const PassengerList& ScheduleManager::getPassengerRegistry() const { return passengerRegistry; }
const ShuttleList& ScheduleManager::getShuttleRegistry() const { return shuttleRegistry; }

vector<const Entity*> ScheduleManager::getAllEntities() const {
    // Gather both passengers and shuttles into a single view for overview display.
    vector<const Entity*> entities;
    entities.reserve(passengerRegistry.size() + shuttleRegistry.size());

    for (size_t i = 0; i < passengerRegistry.size(); ++i) {
        entities.push_back(&passengerRegistry[i]);
    }
    for (size_t i = 0; i < shuttleRegistry.size(); ++i) {
        entities.push_back(&shuttleRegistry[i]);
    }
    return entities;
}

void ScheduleManager::setMatchingStrategy(unique_ptr<IMatchingStrategy> strategy) {
    // Replace the current matching strategy at runtime without changing the caller interface.
    schedulingService.setStrategy(std::move(strategy));
}

string ScheduleManager::getStrategyName() const {
    return schedulingService.getStrategyName();
}

void ScheduleManager::runMatchingAlgorithm() {
    schedulingService.runMatchingAlgorithm(passengerRegistry, shuttleRegistry);
}

const vector<Schedule>& ScheduleManager::getSchedules() const {
    return schedulingService.getSchedules();
}

void ScheduleManager::clearSchedules() {
    // Remove generated schedules and reset assignments before a new matching run.
    schedulingService.clearSchedules();
    passengerRegistry.resetAssignments();
    shuttleRegistry.resetAssignments();
}

bool ScheduleManager::savePassengerData(const string& path) const {
    return dataService.savePassengerData(path, passengerRegistry);
}

bool ScheduleManager::saveShuttleData(const string& path) const {
    return dataService.saveShuttleData(path, shuttleRegistry);
}

bool ScheduleManager::editPassenger(const string& id, const string& newDestination, const string& newTime, int newGroupSize) {
    // Delegate passenger edits to the data service while keeping the controller thin.
    return dataService.editPassenger(passengerRegistry, id, newDestination, newTime, newGroupSize);
}

bool ScheduleManager::editShuttle(const string& id, const string& newDestination, const string& newTime, const string& newModel) {
    // Delegate shuttle edits to the data service while keeping the controller thin.
    return dataService.editShuttle(shuttleRegistry, id, newDestination, newTime, newModel);
}
