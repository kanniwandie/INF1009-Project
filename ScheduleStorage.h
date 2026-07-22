#ifndef SCHEDULE_STORAGE_H
#define SCHEDULE_STORAGE_H

#include "Schedule.h"
#include <string>
#include <vector>
using namespace std;

class ScheduleStorage {
public:
    static void saveSchedules(const string& filename, const vector<Schedule>& schedules);
};

#endif
