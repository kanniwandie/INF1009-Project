#ifndef SCHEDULE_STORAGE_H
#define SCHEDULE_STORAGE_H

#include "Schedule.h"
#include <string>
#include <vector>

class ScheduleStorage {
public:
    static string formatScheduleToString(const Schedule& schedule);
    static bool saveSchedules(const string& filename, const vector<Schedule>& activeSchedules);
};

#endif