#include "ScheduleStorage.h"
#include <fstream>

using namespace std;

string ScheduleStorage::formatScheduleToString(const Schedule& schedule) {
    if (schedule.getPassenger() && schedule.getShuttle()) {
        return schedule.getPassenger()->getID() + "," +
            schedule.getShuttle()->getID() + "," +
            schedule.getPassenger()->getDestination() + "," +
            schedule.getPassenger()->getScheduledTime();
    }
    return "";
}

bool ScheduleStorage::saveSchedules(const string& filename, const vector<Schedule>& activeSchedules) {
    ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    file << "PassengerID,ShuttleID,Destination,ScheduledTime\n";
    for (const auto& sched : activeSchedules) {
        string line = formatScheduleToString(sched);
        if (!line.empty()) {
            file << line << "\n";
        }
    }
    file.close();
    return true;
}