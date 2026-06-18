#include "ShuttleVehicle.h"

ShuttleVehicle::ShuttleVehicle(const DriverlessVehicle& shuttle, bool isAssigned) : DriverlessVehicle(shuttle), isAssigned(isAssigned) {
}

ShuttleVehicle::ShuttleVehicle(const string& id, const string& destination, const string& scheduledTime, bool isAssigned) : DriverlessVehicle(id, destination, scheduledTime), isAssigned(isAssigned) {
}

void ShuttleVehicle::setAssignedStatus(bool status) {
    isAssigned = status;
}

bool ShuttleVehicle::getAssignedStatus() const {
    return isAssigned;
}