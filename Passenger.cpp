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
    // Deliberately does NOT call getScheduledTimeObject().isValid() - that check
    // enforces the shuttle-only 6am-midnight operating window (Requirement 3),
    // which would wrongly reject a legitimate passenger request placed just
    // after midnight (see the S01/P06 spec example). Instead, only check that
    // the time string was actually parseable at all: OperationalTime::parse()
    // uses hour = -1 as a sentinel specifically for "could not parse this,"
    // which a legitimately parsed time (0-23) can never produce.
    const Time& time = getScheduledTimeObject();

    const bool validTime =
        time.getHour() >= 0 &&
        time.getHour() <= 23 &&
        time.getMinute() >= 0 &&
        time.getMinute() <= 59;

    return passengerId.isValid() &&
           groupSize >= 1 &&
           groupSize <= 15 &&
           destination.isValid() &&
           validTime;
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
