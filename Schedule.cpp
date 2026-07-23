#include "Schedule.h"
using namespace std;

Schedule::Schedule(const Passenger* passenger, const ShuttleVehicle* shuttle)
    : assignPassenger(passenger), assignShuttle(shuttle) {
}

Schedule::Schedule(const Schedule& other)
    : assignPassenger(other.assignPassenger), assignShuttle(other.assignShuttle) {
}

Schedule& Schedule::operator=(const Schedule& other) {
    if (this != &other) {
        assignPassenger = other.assignPassenger;
        assignShuttle = other.assignShuttle;
    }
    return *this;
}

const Passenger* Schedule::getPassenger() const { return assignPassenger; }
const ShuttleVehicle* Schedule::getShuttle() const { return assignShuttle; }
