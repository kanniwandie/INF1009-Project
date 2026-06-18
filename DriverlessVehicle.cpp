#include "DriverlessVehicle.h"
using namespace std;

DriverlessVehicle::DriverlessVehicle(const string& id, const string& destination, const string& scheduledTime)
    : Entity(id, destination, scheduledTime) {
}

string DriverlessVehicle::getType() const { return "DriverlessVehicle"; }

string DriverlessVehicle::getDescription() const {
    return "DriverlessVehicle " + id + " -> " + destination + " @ " + scheduledTime;
}
