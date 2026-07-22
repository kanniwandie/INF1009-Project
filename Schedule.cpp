#include "Schedule.h"
using namespace std;

Schedule::Schedule(const Passenger* passenger, const ShuttleVehicle* shuttle)
    : assignPassenger(passenger), assignShuttle(shuttle) {
}

ScheduleList::ScheduleList() : matchingStrategy(make_unique<MinimumDispatchStrategy>()) {}

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

void ScheduleList::setMatchingStrategy(unique_ptr<IMatchingStrategy> strategy) {
    matchingStrategy = std::move(strategy);
    if (!matchingStrategy) {
        matchingStrategy = make_unique<MinimumDispatchStrategy>();
    }
}

void ScheduleList::clearSchedules() { activeSchedules.clear(); }

void ScheduleList::generateSchedules() {
    activeSchedules.clear();
    passengerRegistry.resetAssignments();
    shuttleRegistry.resetAssignments();

    if (!matchingStrategy) {
        matchingStrategy = make_unique<MinimumDispatchStrategy>();
    }

    for (size_t si = 0; si < shuttleRegistry.size(); ++si) {
        auto& shuttle = shuttleRegistry[si];
        if (!shuttle.isValid()) continue;

        for (size_t pi = 0; pi < passengerRegistry.size(); ++pi) {
            auto& passenger = passengerRegistry[pi];
            if (passenger.getAssignedStatus() || !passenger.isValid()) continue;

            if (!matchingStrategy->shouldMatch(passenger, shuttle)) continue;

            const auto* model = shuttle.getModel();
            if (!model) continue;

            int usedCapacity = 0;
            for (const auto& existing : activeSchedules) {
                if (existing.getShuttle() == &shuttle) {
                    usedCapacity += existing.getPassenger()->getGroupSize();
                }
            }

            if (usedCapacity + passenger.getGroupSize() > model->getMaxSeats()) {
                continue;
            }

            passenger.setAssignedStatus(true);
            shuttle.setAssignedStatus(true);
            activeSchedules.emplace_back(&passenger, &shuttle);
        }
    }
}
