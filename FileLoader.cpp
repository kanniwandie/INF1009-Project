#include "FileLoader.h"
#include "Schedule.h"
#include "Passenger.h"
#include "ShuttleVehicle.h"
#include <fstream>
#include <sstream>

namespace {
string trim(const string& value) {
    size_t start = value.find_first_not_of(" \t");
    if (start == string::npos) return "";
    size_t end = value.find_last_not_of(" \t");
    return value.substr(start, end - start + 1);
}
}

namespace {
Passenger createPassengerFromFields(const string& id, const string& destination, const string& time, const string& groupSizeField) {
    int groupSize = 1;
    try {
        groupSize = stoi(trim(groupSizeField));
    } catch (...) {
        groupSize = 1;
    }
    return Passenger(trim(id), trim(destination), trim(time), groupSize);
}

ShuttleVehicle createShuttleFromFields(const string& id, const string& destination, const string& time, const string& modelName) {
    ShuttleVehicle shuttle(trim(id), trim(destination), trim(time));
    string model = trim(modelName);
    if (model == "Small") {
        shuttle.setModel(make_unique<SmallShuttleModel>());
    } else if (model == "Family") {
        shuttle.setModel(make_unique<FamilyShuttleModel>());
    } else if (model == "Premium") {
        shuttle.setModel(make_unique<PremiumShuttleModel>());
    } else {
        shuttle.setModel(make_unique<SmallShuttleModel>());
    }
    return shuttle;
}
}

bool PassengerParser::load(const string& path, PassengerList& passengers, ShuttleList& shuttles) {
    (void)shuttles;
    ifstream file(path);
    if (!file.is_open()) return false;

    string line;
    while (getline(file, line)) {
        if (!parse(line, passengers, shuttles)) {
            continue;
        }
    }
    return true;
}

bool PassengerParser::parse(const string& rawEntry, PassengerList& passengers, ShuttleList& shuttles) const {
    (void)shuttles;
    stringstream ss(rawEntry);
    string id, destination, time, groupSizeField;
    if (!getline(ss, id, ',') || !getline(ss, destination, ',') || !getline(ss, time, ',') || !getline(ss, groupSizeField, ',')) {
        return false;
    }

    passengers.add(createPassengerFromFields(id, destination, time, groupSizeField));
    return true;
}

bool ShuttleParser::load(const string& path, PassengerList& passengers, ShuttleList& shuttles) {
    (void)passengers;
    ifstream file(path);
    if (!file.is_open()) return false;

    string line;
    while (getline(file, line)) {
        if (!parse(line, passengers, shuttles)) {
            continue;
        }
    }
    return true;
}

bool ShuttleParser::parse(const string& rawEntry, PassengerList& passengers, ShuttleList& shuttles) const {
    (void)passengers;
    stringstream ss(rawEntry);
    string id, destination, time, modelName;
    if (!getline(ss, id, ',') || !getline(ss, destination, ',') || !getline(ss, time, ',') || !getline(ss, modelName, ',')) {
        return false;
    }

    shuttles.add(createShuttleFromFields(id, destination, time, modelName));
    return true;
}
