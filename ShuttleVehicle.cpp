/**
 * @file ShuttleVehicle.cpp
 * @brief Implements the shuttle vehicle entity used for route scheduling.
 * @author Chen Xiyuan
 */

#include "ShuttleVehicle.h"
using namespace std;

ShuttleVehicle::ShuttleVehicle(const DriverlessVehicle& shuttle, bool isAssigned)
    : DriverlessVehicle(shuttle), vehicleId(shuttle.getID()), model(make_unique<SmallShuttleModel>()) {
    setAssignedStatus(isAssigned);
}

ShuttleVehicle::ShuttleVehicle(const string& id, const string& destination, const string& scheduledTime, bool isAssigned)
    : DriverlessVehicle(id, destination, scheduledTime), vehicleId(id), model(make_unique<SmallShuttleModel>()) {
    setAssignedStatus(isAssigned);
}

ShuttleVehicle::ShuttleVehicle(const ShuttleVehicle& other)
    : DriverlessVehicle(other), vehicleId(other.vehicleId.getValue()), model(other.model ? other.model->clone() : nullptr) {
    setAssignedStatus(other.getAssignedStatus());
}

ShuttleVehicle& ShuttleVehicle::operator=(const ShuttleVehicle& other) {
    if (this != &other) {
        DriverlessVehicle::operator=(other);
        vehicleId = other.vehicleId;
        model = other.model ? other.model->clone() : nullptr;
        setAssignedStatus(other.getAssignedStatus());
    }
    return *this;
}

void ShuttleVehicle::setVehicleId(const string& id) { vehicleId = VehicleID(id); }
string ShuttleVehicle::getVehicleId() const { return vehicleId.getValue(); }
bool ShuttleVehicle::hasSameID(const VehicleID& other) const { return vehicleId == other; }
bool ShuttleVehicle::hasSameID(const string& other) const { return vehicleId == other; }
void ShuttleVehicle::edit(const string& newDestination, const string& newTime, unique_ptr<ShuttleModel> newModel) {
    setDestination(newDestination);
    setScheduledTime(newTime);
    setModel(std::move(newModel));
}
void ShuttleVehicle::setModel(unique_ptr<ShuttleModel> newModel) { model = std::move(newModel); }
const ShuttleModel* ShuttleVehicle::getModel() const { return model.get(); }

bool ShuttleVehicle::isValid() const {
    return vehicleId.isValid() && destination.isValid() && getScheduledTimeObject().isValid();
}

string ShuttleVehicle::getType() const { return "Shuttle"; }

string ShuttleVehicle::getDescription() const {
    return "Shuttle " + getID() + " -> " + getDestination() + " @ " + getScheduledTime()
        + (getAssignedStatus() ? " [Assigned]" : " [Unassigned]");
}
