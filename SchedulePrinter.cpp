#include "SchedulePrinter.h"
#include <iostream>

using namespace std;

void SchedulePrinter::printSchedule(const Schedule& schedule) {
    if (schedule.getPassenger() && schedule.getShuttle()) {
        cout << "[MATCHED] Pass: " << schedule.getPassenger()->getID()
            << " <---> Shuttle: " << schedule.getShuttle()->getID()
            << " | Dest: " << schedule.getPassenger()->getDestination()
            << " | Time: " << schedule.getPassenger()->getScheduledTime() << "\n";
    }
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
            cout << "Passenger: " << p.getID() << " | Dest: " << p.getDestination() << " | Time: " << p.getScheduledTime() << "\n";
            elementsFound = true;
        }
    }
    if (!elementsFound) cout << "None\n";

    cout << "\n=== UNASSIGNED SHUTTLES ===\n";
    elementsFound = false;
    for (const auto& s : sList.getItems()) {
        if (!s.getAssignedStatus()) {
            cout << "Vehicle: " << s.getID() << " | Dest: " << s.getDestination() << " | Time: " << s.getScheduledTime() << "\n";
            elementsFound = true;
        }
    }
    if (!elementsFound) cout << "None\n";
}