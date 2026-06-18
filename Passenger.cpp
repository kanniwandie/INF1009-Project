#include "Passenger.h"
using namespace std;

Passenger::Passenger(const string& id, const string& destination, const string& scheduledTime, bool isAssigned)
    : Entity(id, destination, scheduledTime), isAssigned(isAssigned) {
}

void Passenger::setAssignedStatus(bool status) { isAssigned = status; }
bool Passenger::getAssignedStatus() const { return isAssigned; }

string Passenger::getType() const { return "Passenger"; }

string Passenger::getDescription() const {
    return "Passenger " + id + " -> " + destination + " @ " + scheduledTime
        + (isAssigned ? " [Assigned]" : " [Unassigned]");
}
