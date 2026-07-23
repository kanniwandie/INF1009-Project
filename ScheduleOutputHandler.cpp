#include "ScheduleOutputHandler.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>

#if defined(_WIN32)
#include <time.h>
#endif

namespace {
string currentTimestamp() {
    time_t now = time(nullptr);
    tm localTime{};

#if defined(_WIN32)
    if (localtime_s(&localTime, &now) != 0) {
        return "unknown";
    }
#else
    if (localtime_r(&now, &localTime) == nullptr) {
        return "unknown";
    }
#endif

    char buffer[20]{};

    if (strftime(
            buffer,
            sizeof(buffer),
            "%Y-%m-%d %H:%M:%S",
            &localTime) == 0) {
        return "unknown";
    }

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

void ConsolePrinter::writeSchedules(const vector<Schedule>& schedules, const string& strategyName) const {
    cout << "\n====================================================================================\n";
    cout << "ACTIVE SCHEDULE PLAN (Strategy: " << strategyName << ")\n";
    cout << "Timestamp Generated: " << currentTimestamp() << "\n";
    cout << "====================================================================================\n";
    cout << left << setw(12) << "Shuttle ID" << "| " << left << setw(18) << "Destination" << "| " << left << setw(14) << "Shuttle Time" << "| " << left << setw(10) << "Model" << "| " << left << setw(12) << "Passenger ID" << "| " << left << setw(18) << "Passenger Time" << "| " << "Group Size\n";
    cout << string(112, '-') << "\n";

    for (const auto& schedule : schedules) {
        const Passenger* passenger = schedule.getPassenger();
        const ShuttleVehicle* shuttle = schedule.getShuttle();
        if (!passenger || !shuttle) continue;
        cout << left << setw(12) << shuttle->getID() << "| " << left << setw(18) << shuttle->getDestination() << "| " << left << setw(14) << formatTime(shuttle->getScheduledTimeObject()) << "| " << left << setw(10) << modelName(*shuttle) << "| " << left << setw(12) << passenger->getID() << "| " << left << setw(18) << formatTime(passenger->getScheduledTimeObject()) << "| " << passenger->getGroupSize() << "\n";
    }
}

void ConsolePrinter::writeUnassigned(const PassengerList& passengers, const ShuttleList& shuttles) const {
    cout << "\n====================================================================================\n";
    cout << "UNASSIGNED REGISTRY ENTRIES\n";
    cout << "====================================================================================\n";
    cout << "[Unassigned Shuttles]\n";
    cout << left << setw(12) << "Shuttle ID" << "| " << left << setw(18) << "Destination" << "| " << left << setw(18) << "Operational Time" << "| " << "Model\n";
    cout << string(76, '-') << "\n";
    for (const auto& shuttle : shuttles.getItems()) {
        if (!shuttle.getAssignedStatus()) {
            cout << left << setw(12) << shuttle.getID() << "| " << left << setw(18) << shuttle.getDestination() << "| " << left << setw(18) << formatTime(shuttle.getScheduledTimeObject()) << "| " << modelName(shuttle) << "\n";
        }
    }

    cout << "\n[Unassigned Passengers]\n";
    cout << left << setw(14) << "Passenger ID" << "| " << left << setw(18) << "Destination" << "| " << left << setw(18) << "Requested Time" << "| " << "Group Size\n";
    cout << string(76, '-') << "\n";
    for (const auto& passenger : passengers.getItems()) {
        if (!passenger.getAssignedStatus()) {
            cout << left << setw(14) << passenger.getID() << "| " << left << setw(18) << passenger.getDestination() << "| " << left << setw(18) << formatTime(passenger.getScheduledTimeObject()) << "| " << passenger.getGroupSize() << "\n";
        }
    }
}

TextFileFormatter::TextFileFormatter(string path) : outputPath(std::move(path)) {}

bool TextFileFormatter::saveSchedules(const vector<Schedule>& schedules, const string& strategyName) const {
    ofstream file(outputPath);

    if (!file.is_open()) {
        cerr << "Unable to write schedule output to "
             << outputPath << "\n";
        return false;
    }

    file << "====================================================================================\n";
    file << "ACTIVE SCHEDULE PLAN (Strategy: " << strategyName << ")\n";
    file << "Timestamp Generated: " << currentTimestamp() << "\n";
    file << "====================================================================================\n";

    file << left
         << setw(12) << "Shuttle ID" << "| "
         << setw(18) << "Destination" << "| "
         << setw(14) << "Shuttle Time" << "| "
         << setw(18) << "Model" << "| "
         << setw(12) << "Passenger ID" << "| "
         << setw(18) << "Passenger Time" << "| "
         << "Group Size\n";

    file << string(112, '-') << "\n";

    for (const auto& schedule : schedules) {
        const Passenger* passenger = schedule.getPassenger();

        const ShuttleVehicle* shuttle = schedule.getShuttle();

        if (!passenger || !shuttle) {
            continue;
        }

        file << left
             << setw(12) << shuttle->getID() << "| "
             << setw(18) << shuttle->getDestination() << "| "
             << setw(14)
             << formatTime(shuttle->getScheduledTimeObject())
             << "| "
             << setw(18) << modelName(*shuttle) << "| "
             << setw(12) << passenger->getID() << "| "
             << setw(18)
             << formatTime(passenger->getScheduledTimeObject())
             << "| "
             << passenger->getGroupSize() << "\n";
    }

    return file.good();
}

void TextFileFormatter::writeSchedules(const vector<Schedule>& schedules, const string& strategyName) const {
    (void)saveSchedules(schedules, strategyName);
}

void ConsolePrinter::writeAllData(const PassengerList& passengers, const ShuttleList& shuttles) const {
    cout << "\n====================================================================================\n";
    cout << "ALL REGISTERED PASSENGERS AND SHUTTLES\n";
    cout << "====================================================================================\n";

    cout << "\n[Passengers]\n";
    cout << left << setw(14) << "Passenger ID" << "| " << left << setw(18) << "Destination" << "| " << left << setw(18) << "Requested Time" << "| " << left << setw(10) << "Group Size" << "| " << "Status\n";
    cout << string(92, '-') << "\n";
    for (const auto& passenger : passengers.getItems()) {
        cout << left << setw(14) << passenger.getID() << "| " << left << setw(18) << passenger.getDestination() << "| " << left << setw(18) << formatTime(passenger.getScheduledTimeObject()) << "| " << left << setw(10) << passenger.getGroupSize() << "| " << (passenger.getAssignedStatus() ? "Assigned" : "Unassigned") << "\n";
    }

    cout << "\n[Shuttles]\n";
    cout << left << setw(12) << "Shuttle ID" << "| " << left << setw(18) << "Destination" << "| " << left << setw(18) << "Operational Time" << "| " << left << setw(18) << "Model" << "| " << "Status\n";
    cout << string(86, '-') << "\n";
    for (const auto& shuttle : shuttles.getItems()) {
        cout << left << setw(12) << shuttle.getID() << "| " << left << setw(18) << shuttle.getDestination() << "| " << left << setw(18) << formatTime(shuttle.getScheduledTimeObject()) << "| " << left << setw(18) << modelName(shuttle) << "| " << (shuttle.getAssignedStatus() ? "Assigned" : "Unassigned") << "\n";
    }
}

void ConsolePrinter::writeEntityOverview(const vector<const Entity*>& entities) const {
    cout << "\n====================================================================================\n";
    cout << "POLYMORPHIC ENTITY OVERVIEW (single loop over vector<const Entity*>)\n";
    cout << "====================================================================================\n";
    cout << left << setw(9) << "Type" << "| " << left << setw(9) << "Valid?" << "| " << "Description\n";
    cout << string(80, '-') << "\n";

    // entities mixes Passenger* and ShuttleVehicle* objects (upcast to Entity*).
    // getType()/isValid()/getDescription() are pure virtual on Entity, so this one
    // loop dispatches to the correct override for each element at runtime without
    // ever checking (or needing to know) which concrete type it is looking at.
    for (const Entity* entity : entities) {
        if (!entity) continue;
        cout << left << setw(9) << entity->getType() << "| "
             << left << setw(9) << (entity->isValid() ? "Valid" : "Invalid") << "| "
             << entity->getDescription() << "\n";
    }
}


void TextFileFormatter::writeUnassigned(const PassengerList& passengers, const ShuttleList& shuttles) const {
    ofstream file(outputPath, ios::app);
    if (!file.is_open()) {
        cerr << "Unable to append unassigned output to " << outputPath << "\n";
        return;
    }

    file << "\n====================================================================================\n";
    file << "UNASSIGNED REGISTRY ENTRIES\n";
    file << "====================================================================================\n";
    file << "[Unassigned Shuttles]\n";
    file << left << setw(12) << "Shuttle ID" << "| " << left << setw(18) << "Destination" << "| " << left << setw(18) << "Operational Time" << "| " << "Model\n";
    file << string(76, '-') << "\n";
    for (const auto& shuttle : shuttles.getItems()) {
        if (!shuttle.getAssignedStatus()) {
            file << left << setw(12) << shuttle.getID() << "| " << left << setw(18) << shuttle.getDestination() << "| " << left << setw(18) << formatTime(shuttle.getScheduledTimeObject()) << "| " << modelName(shuttle) << "\n";
        }
    }

    file << "\n[Unassigned Passengers]\n";
    file << left << setw(14) << "Passenger ID" << "| " << left << setw(18) << "Destination" << "| " << left << setw(18) << "Requested Time" << "| " << "Group Size\n";
    file << string(76, '-') << "\n";
    for (const auto& passenger : passengers.getItems()) {
        if (!passenger.getAssignedStatus()) {
            file << left << setw(14) << passenger.getID() << "| " << left << setw(18) << passenger.getDestination() << "| " << left << setw(18) << formatTime(passenger.getScheduledTimeObject()) << "| " << passenger.getGroupSize() << "\n";
        }
    }
}

void TextFileFormatter::writeAllData(const PassengerList& passengers, const ShuttleList& shuttles) const {
    ofstream file(outputPath, ios::app);
    if (!file.is_open()) {
        cerr << "Unable to append all-data output to " << outputPath << "\n";
        return;
    }

    file << "\n====================================================================================\n";
    file << "ALL REGISTERED PASSENGERS AND SHUTTLES\n";
    file << "====================================================================================\n";
    file << "\n[Passengers]\n";
    file << left << setw(14) << "Passenger ID" << "| " << left << setw(18) << "Destination" << "| " << left << setw(18) << "Requested Time" << "| " << left << setw(10) << "Group Size" << "| " << "Status\n";
    file << string(92, '-') << "\n";
    for (const auto& passenger : passengers.getItems()) {
        file << left << setw(14) << passenger.getID() << "| " << left << setw(18) << passenger.getDestination() << "| " << left << setw(18) << formatTime(passenger.getScheduledTimeObject()) << "| " << left << setw(10) << passenger.getGroupSize() << "| " << (passenger.getAssignedStatus() ? "Assigned" : "Unassigned") << "\n";
    }

    file << "\n[Shuttles]\n";
    file << left << setw(12) << "Shuttle ID" << "| " << left << setw(18) << "Destination" << "| " << left << setw(18) << "Operational Time" << "| " << left << setw(10) << "Model" << "| " << "Status\n";
    file << string(86, '-') << "\n";
    for (const auto& shuttle : shuttles.getItems()) {
        file << left << setw(12) << shuttle.getID() << "| " << left << setw(18) << shuttle.getDestination() << "| " << left << setw(18) << formatTime(shuttle.getScheduledTimeObject()) << "| " << left << setw(10) << modelName(shuttle) << "| " << (shuttle.getAssignedStatus() ? "Assigned" : "Unassigned") << "\n";
    }
}

void TextFileFormatter::writeEntityOverview(const vector<const Entity*>& entities) const {
    ofstream file(outputPath, ios::app);
    if (!file.is_open()) {
        cerr << "Unable to append entity overview to " << outputPath << "\n";
        return;
    }

    file << "\n====================================================================================\n";
    file << "POLYMORPHIC ENTITY OVERVIEW (single loop over vector<const Entity*>)\n";
    file << "====================================================================================\n";
    file << left << setw(9) << "Type" << "| " << left << setw(9) << "Valid?" << "| " << "Description\n";
    file << string(80, '-') << "\n";

    // Same polymorphic dispatch as ConsolePrinter::writeEntityOverview, just
    // written to a file instead of the console - the entity-handling code is
    // identical either way because it only ever touches the Entity interface.
    for (const Entity* entity : entities) {
        if (!entity) continue;
        file << left << setw(9) << entity->getType() << "| "
             << left << setw(9) << (entity->isValid() ? "Valid" : "Invalid") << "| "
             << entity->getDescription() << "\n";
    }
}
