#include "SchedulePrinter.h"
#include <iostream>
using namespace std;

void SchedulePrinter::printSchedule(const Schedule& schedule) {
    cout << "[MATCHED] " << schedule.getPassengerID()
         << " <---> " << schedule.getShuttleID()
         << " | Dest: " << schedule.getDestination()
         << " | Time: " << schedule.getScheduledTime() << "\n";
}

void SchedulePrinter::printActiveSchedules(const vector<Schedule>& activeSchedules) {
    cout << "\n=== ACTIVE SCHEDULES ===\n";
    if (activeSchedules.empty()) {
        cout << "No schedules currently active.\n";
        return;
    }
    for (const auto& sched : activeSchedules) {
        printSchedule(sched);
    }
}

void SchedulePrinter::printUnassignedEntities(const PassengerList& pList, const ShuttleList& sList) {
    cout << "\n=== UNASSIGNED PASSENGERS ===\n";
    bool elementsFound = false;
    for (const auto& p : pList.getItems()) {
        if (!p.getAssignedStatus()) {
            cout << p.getDescription() << "\n";
            elementsFound = true;
        }
    }
    if (!elementsFound) cout << "None\n";

    cout << "\n=== UNASSIGNED SHUTTLES ===\n";
    elementsFound = false;
    for (const auto& s : sList.getItems()) {
        if (!s.getAssignedStatus()) {
            cout << s.getDescription() << "\n";
            elementsFound = true;
        }
    }
    if (!elementsFound) cout << "None\n";
}
