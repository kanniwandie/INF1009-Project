#include "IMatchingStrategy.h"
#include "Passenger.h"
#include "ShuttleVehicle.h"
#include <memory>

#define ARRIVAL_WINDOW_MINUTES 10

namespace {
int toMinutes(const Time& time) {
    return time.getHour() * 60 + time.getMinute();
}

bool isWithinArrivalWindow(const Time& shuttleTime, const Time& passengerTime) {
    int shuttleMinutes = toMinutes(shuttleTime);
    int passengerMinutes = toMinutes(passengerTime);
    int earlyLimit = passengerMinutes - ARRIVAL_WINDOW_MINUTES;
    return shuttleMinutes >= earlyLimit && shuttleMinutes <= passengerMinutes;
}
}

bool MinimumDispatchStrategy::shouldMatch(const Passenger& passenger, const ShuttleVehicle& shuttle) const {
    if (passenger.getAssignedStatus()) {
        return false;
    }

    if (passenger.getDestination() != shuttle.getDestination()) {
        return false;
    }

    const auto& pTime = passenger.getScheduledTimeObject();
    const auto& sTime = shuttle.getScheduledTimeObject();

    return isWithinArrivalWindow(sTime, pTime);
}

string MinimumDispatchStrategy::getName() const { return "Minimum Dispatch"; }

bool EarliestArrivalStrategy::shouldMatch(const Passenger& passenger, const ShuttleVehicle& shuttle) const {
    if (passenger.getAssignedStatus()) {
        return false;
    }

    if (passenger.getDestination() != shuttle.getDestination()) {
        return false;
    }

    const auto& pTime = passenger.getScheduledTimeObject();
    const auto& sTime = shuttle.getScheduledTimeObject();

    return isWithinArrivalWindow(sTime, pTime);
}

string EarliestArrivalStrategy::getName() const { return "Earliest Arrival"; }
