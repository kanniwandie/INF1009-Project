/**
 * @file DriverlessVehicle.cpp
 * @brief Implements the autonomous vehicle base class used by shuttle entities.
 * @author Chen Xiyuan
 */

#include "DriverlessVehicle.h"
using namespace std;

DriverlessVehicle::DriverlessVehicle(const string& id, const string& destination, const string& scheduledTime)
    : Entity(id, destination, scheduledTime) {
}

string DriverlessVehicle::getType() const { return "DriverlessVehicle"; }

string DriverlessVehicle::getDescription() const {
    return "DriverlessVehicle " + getID() + " -> " + getDestination() + " @ " + getScheduledTime();
}
