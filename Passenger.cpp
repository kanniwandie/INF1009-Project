/**
 * @file Passenger.cpp
 * @brief Implements the passenger entity and its validation behaviour.
 * @author Chen Xiyuan
 */

#include "Passenger.h"
using namespace std;

Passenger::Passenger(const string& id, const string& destination, const string& scheduledTime, int groupSize, bool isAssigned)
    : Entity(id, destination, scheduledTime), passengerId(id), groupSize(groupSize) {
    setAssignedStatus(isAssigned);
}

void Passenger::setGroupSize(int size) { groupSize = size; }
int Passenger::getGroupSize() const { return groupSize; }

void Passenger::edit(const string& newDestination, const string& newTime, int newGroupSize) {
    setDestination(newDestination);
    setScheduledTime(newTime);
    setGroupSize(newGroupSize);
}

bool Passenger::isValid() const {
    return passengerId.isValid() &&
           groupSize >= 1 &&
           groupSize <= 15 &&
           destination.isValid() &&
           getScheduledTimeObject().isValid();
} 

bool Passenger::hasSameID(const PassengerID& other) const {
    return passengerId == other;
}

bool Passenger::hasSameID(const string& other) const {
    return passengerId == other;
}

string Passenger::getType() const { return "Passenger"; }

string Passenger::getDescription() const {
    return "Passenger " + id + " -> " + getDestination() + " @ " + getScheduledTime()
        + (getAssignedStatus() ? " [Assigned]" : " [Unassigned]");
}
