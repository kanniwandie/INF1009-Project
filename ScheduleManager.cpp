#include "ScheduleManager.h"
#include "Passenger.h"
#include "ShuttleVehicle.h"
#include <utility>
using namespace std;

LoadResult ScheduleManager::loadAllSystemData(const string& folder) {
    passengerRegistry.clear();
    shuttleRegistry.clear();
    return SystemDataService::loadInitialData(passengerRegistry, shuttleRegistry, folder);
}

PassengerList& ScheduleManager::getPassengerRegistry() { return passengerRegistry; }
ShuttleList& ScheduleManager::getShuttleRegistry() { return shuttleRegistry; }
const PassengerList& ScheduleManager::getPassengerRegistry() const { return passengerRegistry; }
const ShuttleList& ScheduleManager::getShuttleRegistry() const { return shuttleRegistry; }

vector<const Entity*> ScheduleManager::getAllEntities() const {
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
    return dataService.editPassenger(passengerRegistry, id, newDestination, newTime, newGroupSize);
}

bool ScheduleManager::editShuttle(const string& id, const string& newDestination, const string& newTime, const string& newModel) {
    return dataService.editShuttle(shuttleRegistry, id, newDestination, newTime, newModel);
}
