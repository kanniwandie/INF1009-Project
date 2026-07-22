#include "SchedulePrinter.h"
#include "ScheduleOutputHandler.h"
#include <iostream>
using namespace std;

void SchedulePrinter::printSchedule(const Schedule& schedule) {
    if (schedule.getPassenger() && schedule.getShuttle()) {
        cout << "[MATCHED] " << schedule.getPassenger()->getID()
             << " <---> " << schedule.getShuttle()->getID()
             << " | Dest: " << schedule.getPassenger()->getDestination()
             << " | Time: " << schedule.getPassenger()->getScheduledTime() << "\n";
    }
}

void SchedulePrinter::printActiveSchedules(const vector<Schedule>& activeSchedules) {
    ConsolePrinter printer;
    printer.writeSchedules(activeSchedules, "Minimum Dispatch");
}

void SchedulePrinter::printUnassignedEntities(const PassengerList& pList, const ShuttleList& sList) {
    ConsolePrinter printer;
    printer.writeUnassigned(pList, sList);
}
