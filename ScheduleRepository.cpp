#include "ScheduleRepository.h"
using namespace std;

void ScheduleRepository::addSchedule(const Schedule& schedule) {
    activeSchedules.push_back(schedule);
}

const vector<Schedule>& ScheduleRepository::getSchedules() const {
    return activeSchedules;
}

void ScheduleRepository::clear() {
    activeSchedules.clear();
}
