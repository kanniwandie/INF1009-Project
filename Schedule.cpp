#include "Schedule.h"

Schedule::Schedule(Passenger* passenger, ShuttleVehicle* shuttle, bool assigned)
    : assignPassenger(passenger), assignShuttle(shuttle) {
    if (assigned && assignPassenger && assignShuttle) {
        assignPassenger->setAssignedStatus(true);
        assignShuttle->setAssignedStatus(true);
    }
}

Schedule::Schedule(const Schedule& other) {
    assignPassenger = other.assignPassenger;
    assignShuttle = other.assignShuttle;
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

PassengerList& ScheduleList::getPassengerRegistry() { return passengerRegistry; }
ShuttleList& ScheduleList::getShuttleRegistry() { return shuttleRegistry; }
const vector<Schedule>& ScheduleList::getActiveSchedules() const { return activeSchedules; }

void ScheduleList::generateSchedules() {
    activeSchedules.clear();
    passengerRegistry.resetAssignments();
    shuttleRegistry.resetAssignments();

    auto& passengers = passengerRegistry.getModifiableItems();
    auto& shuttles = shuttleRegistry.getModifiableItems();

    for (auto& p : passengers) {
        for (auto& s : shuttles) {
            if (!p.getAssignedStatus() && !s.getAssignedStatus()) {
                if (p.getDestination() == s.getDestination() && p.getScheduledTime() == s.getScheduledTime()) {
                    activeSchedules.push_back(Schedule(&p, &s, true));
                    break;
                }
            }
        }
    }
}