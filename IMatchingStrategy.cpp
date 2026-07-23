#include "IMatchingStrategy.h"
#include "Passenger.h"
#include "ShuttleVehicle.h"
#include "Registry.h"
#include "ScheduleRepository.h"
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

#define ARRIVAL_WINDOW_MINUTES 10

namespace {

int toMinutes(const Time& time) {
    return time.getHour() * 60 + time.getMinute();
}

// A shuttle may pick up a passenger group if it arrives no more than 10 minutes
// before the passenger's requested time, and never after it (Application Requirement 5).
// Minutes are treated on a circular 24-hour clock (mod 1440) so a shuttle at 11:59pm
// correctly counts as a few minutes early for a passenger requesting 12:05am, since the
// service day runs continuously from 6am to midnight without a hard reset at 00:00.
bool isWithinArrivalWindow(const Time& shuttleTime, const Time& passengerTime) {
    const int MINUTES_PER_DAY = 24 * 60;
    int shuttleMinutes = toMinutes(shuttleTime);
    int passengerMinutes = toMinutes(passengerTime);

    int minutesEarly = ((passengerMinutes - shuttleMinutes) % MINUTES_PER_DAY + MINUTES_PER_DAY) % MINUTES_PER_DAY;
    return minutesEarly <= ARRIVAL_WINDOW_MINUTES;
}

bool isEligiblePair(const Passenger& passenger, const ShuttleVehicle& shuttle) {
    if (passenger.getAssignedStatus() || !passenger.isValid()) return false;
    if (!shuttle.isValid()) return false;
    if (passenger.getDestination() != shuttle.getDestination()) return false;
    return isWithinArrivalWindow(shuttle.getScheduledTimeObject(), passenger.getScheduledTimeObject());
}

} // namespace

void MinimumDispatchStrategy::match(PassengerList& passengers, ShuttleList& shuttles, ScheduleRepository& repository) const {
    vector<ShuttleVehicle*> candidates;
    for (size_t si = 0; si < shuttles.size(); ++si) {
        if (shuttles[si].isValid()) {
            candidates.push_back(&shuttles[si]);
        }
    }

    // Largest capacity first so each dispatched shuttle absorbs as many passenger
    // groups as it can hold before another shuttle is used at all.
    sort(candidates.begin(), candidates.end(), [](const ShuttleVehicle* a, const ShuttleVehicle* b) {
        int seatsA = a->getModel() ? a->getModel()->getMaxSeats() : 0;
        int seatsB = b->getModel() ? b->getModel()->getMaxSeats() : 0;
        if (seatsA != seatsB) return seatsA > seatsB;
        return a->getScheduledTimeObject().compare(b->getScheduledTimeObject()) < 0;
    });

    for (ShuttleVehicle* shuttle : candidates) {
        const ShuttleModel* model = shuttle->getModel();
        if (!model) continue;

        int usedCapacity = 0;
        for (size_t pi = 0; pi < passengers.size(); ++pi) {
            Passenger& passenger = passengers[pi];
            if (!isEligiblePair(passenger, *shuttle)) continue;
            if (usedCapacity + passenger.getGroupSize() > model->getMaxSeats()) continue;

            passenger.setAssignedStatus(true);
            shuttle->setAssignedStatus(true);
            usedCapacity += passenger.getGroupSize();
            repository.addSchedule(Schedule(&passenger, shuttle));
        }
    }
}

string MinimumDispatchStrategy::getName() const { return "Minimum Dispatch"; }

void EarliestArrivalStrategy::match(PassengerList& passengers, ShuttleList& shuttles, ScheduleRepository& repository) const {
    unordered_map<ShuttleVehicle*, int> usedCapacity;

    for (size_t pi = 0; pi < passengers.size(); ++pi) {
        Passenger& passenger = passengers[pi];
        if (passenger.getAssignedStatus() || !passenger.isValid()) continue;

        ShuttleVehicle* bestShuttle = nullptr;
        for (size_t si = 0; si < shuttles.size(); ++si) {
            ShuttleVehicle& shuttle = shuttles[si];
            if (!isEligiblePair(passenger, shuttle)) continue;

            const ShuttleModel* model = shuttle.getModel();
            if (!model) continue;

            int used = usedCapacity.count(&shuttle) ? usedCapacity[&shuttle] : 0;
            if (used + passenger.getGroupSize() > model->getMaxSeats()) continue;

            // Among all eligible shuttles, prefer the one arriving earliest -
            // this minimizes the passenger's wait, even if a larger shuttle
            // dispatch count results.
            if (!bestShuttle || shuttle.getScheduledTimeObject().compare(bestShuttle->getScheduledTimeObject()) < 0) {
                bestShuttle = &shuttle;
            }
        }

        if (bestShuttle) {
            passenger.setAssignedStatus(true);
            bestShuttle->setAssignedStatus(true);
            usedCapacity[bestShuttle] += passenger.getGroupSize();
            repository.addSchedule(Schedule(&passenger, bestShuttle));
        }
    }
}

string EarliestArrivalStrategy::getName() const { return "Earliest Arrival"; }
