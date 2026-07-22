#include "ScheduleStorage.h"
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

namespace {
string currentTimestamp() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    if (localTime == nullptr) {
        return "unknown";
    }

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);
    return string(buffer);
}

string modelName(const ShuttleVehicle& shuttle) {
    if (shuttle.getModel() == nullptr) {
        return "Unknown";
    }
    return shuttle.getModel()->getName();
}

string formatTime(const Time& time) {
    return time.toString();
}
}

void ScheduleStorage::saveSchedules(const string& filename, const vector<Schedule>& schedules) {
    ofstream out(filename);
    if (!out.is_open()) {
        cerr << "Unable to save schedule archive to " << filename << "\n";
        return;
    }

    out << "====================================================================================\n";
    out << "ACTIVE SCHEDULE PLAN (Strategy: Minimum Dispatch)\n";
    out << "Timestamp Generated: " << currentTimestamp() << "\n";
    out << "====================================================================================\n";
    out << left << setw(12) << "Shuttle ID" << "| " << left << setw(18) << "Destination" << "| " << left << setw(14) << "Shuttle Time" << "| " << left << setw(10) << "Model" << "| " << left << setw(12) << "Passenger ID" << "| " << left << setw(18) << "Passenger Time" << "| " << "Group Size\n";
    out << string(112, '-') << "\n";

    for (const auto& schedule : schedules) {
        const Passenger* passenger = schedule.getPassenger();
        const ShuttleVehicle* shuttle = schedule.getShuttle();
        if (!passenger || !shuttle) continue;

        out << left << setw(12) << shuttle->getID() << "| "
            << left << setw(18) << shuttle->getDestination() << "| "
            << left << setw(14) << formatTime(shuttle->getScheduledTimeObject()) << "| "
            << left << setw(10) << modelName(*shuttle) << "| "
            << left << setw(12) << passenger->getID() << "| "
            << left << setw(18) << formatTime(passenger->getScheduledTimeObject()) << "| "
            << passenger->getGroupSize() << "\n";
    }
}
