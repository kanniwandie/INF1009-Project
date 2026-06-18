#ifndef SCHEDULE_PRINTER_H
#define SCHEDULE_PRINTER_H

#include "Schedule.h"
#include <vector>

class SchedulePrinter {
public:
    static void printSchedule(const Schedule& schedule);
    static void printActiveSchedules(const vector<Schedule>& activeSchedules);
    static void printUnassignedEntities(const PassengerList& pList, const ShuttleList& sList);
};

#endif