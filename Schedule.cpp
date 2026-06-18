#include "Schedule.h"
using namespace std;

Schedule::Schedule(const string& pID, const string& sID,
                   const string& dest, const string& time)
    : passengerID(pID), shuttleID(sID), destination(dest), scheduledTime(time) {
}

const string& Schedule::getPassengerID() const { return passengerID; }
const string& Schedule::getShuttleID() const { return shuttleID; }
const string& Schedule::getDestination() const { return destination; }
const string& Schedule::getScheduledTime() const { return scheduledTime; }

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
                    activeSchedules.emplace_back(p.getID(), s.getID(), p.getDestination(), p.getScheduledTime());
                    break;
                }
            }
        }
    }
}
