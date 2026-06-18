#include "Passenger.h"

using namespace std;

Passenger::Passenger(const string& id, const string& destination, const string& scheduledTime, bool isAssigned) : Entity(id, destination, scheduledTime), isAssigned(isAssigned) {
}

void Passenger::setAssignedStatus(bool status) { isAssigned = status; }
bool Passenger::getAssignedStatus() const { return isAssigned; }