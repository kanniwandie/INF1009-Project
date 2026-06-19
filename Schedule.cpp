#include "Schedule.h"
using namespace std;

Schedule::Schedule(const Passenger* passenger, const ShuttleVehicle* shuttle)
    : assignPassenger(passenger), assignShuttle(shuttle) {
}

// Copy Constructor 
Schedule::Schedule(const Schedule& other) {
    assignPassenger = other.assignPassenger;
    assignShuttle = other.assignShuttle;
}

// Copy Assignment Operator 
Schedule& Schedule::operator=(const Schedule& other) {
    if (this != &other) { // Guard against self-assignment
        assignPassenger = other.assignPassenger;
        assignShuttle = other.assignShuttle;
    }
    return *this;
}

const Passenger* Schedule::getPassenger() const { return assignPassenger; }
const ShuttleVehicle* Schedule::getShuttle() const { return assignShuttle; }

PassengerList& ScheduleList::getPassengerRegistry() { return passengerRegistry; }
ShuttleList& ScheduleList::getShuttleRegistry() { return shuttleRegistry; }
const vector<Schedule>& ScheduleList::getActiveSchedules() const { return activeSchedules; }

void ScheduleList::clearSchedules() { activeSchedules.clear(); }

void ScheduleList::generateSchedules() {
    activeSchedules.clear();
    passengerRegistry.resetAssignments();
    shuttleRegistry.resetAssignments();

    for (size_t pi = 0; pi < passengerRegistry.size(); ++pi) {
        auto& p = passengerRegistry[pi];
        if (p.getAssignedStatus()) continue;

        for (size_t si = 0; si < shuttleRegistry.size(); ++si) {
            auto& s = shuttleRegistry[si];
            if (!s.getAssignedStatus()) {
                if (p.getDestination() == s.getDestination() && p.getScheduledTime() == s.getScheduledTime()) {
                    p.setAssignedStatus(true);
                    s.setAssignedStatus(true);
                    activeSchedules.emplace_back(&p, &s);
                    break;
                }
            }
        }
    }
}
