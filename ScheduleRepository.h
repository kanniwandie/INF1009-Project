#ifndef SCHEDULE_REPOSITORY_H
#define SCHEDULE_REPOSITORY_H

#include "Schedule.h"
#include <vector>
using namespace std;

// Purpose: Owns the collection of currently active (computed) schedules. Extracted
// from the former ScheduleList god-class so that "where schedules are stored" is a
// single, focused responsibility (SRP), independent of how they were computed.
class ScheduleRepository {
private:
    vector<Schedule> activeSchedules;

public:
    void addSchedule(const Schedule& schedule);
    const vector<Schedule>& getSchedules() const;
    void clear();
};

#endif
