#include "ScheduleStorage.h"
#include <fstream>
#include <iostream>
using namespace std;

string ScheduleStorage::formatScheduleToString(const Schedule& schedule) {
    if (schedule.getPassenger() && schedule.getShuttle()) {
        return schedule.getPassenger()->getID() + ","
             + schedule.getPassenger()->getDestination() + ","
             + schedule.getPassenger()->getScheduledTime() + ","
             + schedule.getShuttle()->getID() + ","
             + schedule.getShuttle()->getDestination() + ","
             + schedule.getShuttle()->getScheduledTime();
    }
    return "";
}

bool ScheduleStorage::saveSchedules(const string& filename, const vector<Schedule>& activeSchedules) {
    if (activeSchedules.empty()) {
        cout << "No schedules to save. Generate schedules first.\n";
        return false;
    }

    ofstream file(filename);
    if (!file.is_open()) return false;

    file << "PassengerID,PassengerDest,PassengerTime,ShuttleID,ShuttleDest,ShuttleTime\n";
    for (const auto& sched : activeSchedules) {
        string line = formatScheduleToString(sched);
        if (!line.empty()) {
            file << line << "\n";
        }
    }
    file.close();
    return true;
}
