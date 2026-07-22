#ifndef SCHEDULE_PRINTER_H
#define SCHEDULE_PRINTER_H

#include "Schedule.h"
#include <vector>
using namespace std;

// Author: [Your Name]
// Purpose: Compatibility wrapper for the schedule output formatter layer.
class SchedulePrinter {
public:
    static void printSchedule(const Schedule& schedule);
    static void printActiveSchedules(const vector<Schedule>& activeSchedules);
    static void printUnassignedEntities(const PassengerList& pList, const ShuttleList& sList);
};

#endif
