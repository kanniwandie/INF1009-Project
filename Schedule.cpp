/**
 * @file Schedule.cpp
 * @brief Implements the schedule value object used by the matching engine.
 * @author Lee Jie Ying Jade, Yap Hui Xin
 */
#include "Schedule.h"
using namespace std;

Schedule::Schedule(const Passenger* passenger, const ShuttleVehicle* shuttle)
    : assignPassenger(passenger), assignShuttle(shuttle) {
    // Store the matched passenger and shuttle references for later rendering.
}

Schedule::Schedule(const Schedule& other)
    : assignPassenger(other.assignPassenger), assignShuttle(other.assignShuttle) {
    // Copy the assignment references from another schedule object.
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
