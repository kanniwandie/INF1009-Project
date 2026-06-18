#include "ScheduleStorage.h"
#include <fstream>
using namespace std;

string ScheduleStorage::formatScheduleToString(const Schedule& schedule) {
    return schedule.getPassengerID() + ","
         + schedule.getShuttleID() + ","
         + schedule.getDestination() + ","
         + schedule.getScheduledTime();
}

bool ScheduleStorage::saveSchedules(const string& filename, const vector<Schedule>& activeSchedules) {
    ofstream file(filename);
    if (!file.is_open()) return false;

    file << "PassengerID,ShuttleID,Destination,ScheduledTime\n";
    for (const auto& sched : activeSchedules) {
        file << formatScheduleToString(sched) << "\n";
    }
    file.close();
    return true;
}
