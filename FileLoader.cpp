#include "FileLoader.h"
#include "Registry.h"
#include "Passenger.h"
#include "ShuttleVehicle.h"
#include "ShuttleModel.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>

namespace {
string trim(const string& value) {
    size_t start = value.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = value.find_last_not_of(" \t\r\n");
    return value.substr(start, end - start + 1);
}

string normalizeModel(string model) {
    model = trim(model);

    transform(model.begin(), model.end(), model.begin(), [](unsigned char ch) {
            return static_cast<char>(tolower(ch));
        }
    );

    if (model == "small") {
        return "Small";
    }

    if (model == "family") {
        return "Family";
    }

    if (model == "premium") {
        return "Premium";
    }

    return "";
}
}

namespace {
Passenger createPassengerFromFields(const string& id, const string& destination, const string& time, const string& groupSizeField) {
    int groupSize;
    try {
        groupSize = stoi(trim(groupSizeField));
    } catch (...) {
        // Deliberately NOT defaulting to a plausible-looking group size like 1
        // here: that would make a corrupted/non-numeric field (e.g. "abc") in
        // a data file silently masquerade as a legitimate booking. -1 fails
        // Passenger::isValid()'s groupSize > 0 check, so the entity is
        // correctly reported as invalid instead of quietly accepted.
        groupSize = -1;
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
    int lineNumber = 0;
    while (getline(file, line)) {
        ++lineNumber;
        if (trim(line).empty()) continue;
        if (!parse(line, passengers, shuttles)) {
            cerr << "[Warning] " << path << " line " << lineNumber << ": malformed or duplicate passenger entry skipped: \"" << line << "\"\n";
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

    Passenger passenger = createPassengerFromFields(id, destination, time, groupSizeField);

    if (!passenger.isValid()) {
        return false;
    }

    return passengers.add(passenger); 
}

bool ShuttleParser::load(const string& path, PassengerList& passengers, ShuttleList& shuttles) {
    (void)passengers;
    ifstream file(path);
    if (!file.is_open()) return false;

    string line;
    int lineNumber = 0;
    while (getline(file, line)) {
        ++lineNumber;
        if (trim(line).empty()) continue;
        if (!parse(line, passengers, shuttles)) {
            cerr << "[Warning] " << path << " line " << lineNumber << ": malformed or duplicate shuttle entry skipped: \"" << line << "\"\n";
        }
    }
    return true;
}

bool ShuttleParser::parse(const string& rawEntry, PassengerList& passengers, ShuttleList& shuttles) const {
    (void)passengers;

    stringstream ss(rawEntry);
    string id, destination, time, modelName;

    if (!getline(ss, id, ',') ||
        !getline(ss, destination, ',') ||
        !getline(ss, time, ',') ||
        !getline(ss, modelName, ',')) {
        return false;
    }

    modelName = normalizeModel(modelName);

    if (modelName.empty()) {
        return false;
    }

    ShuttleVehicle shuttle = createShuttleFromFields(id, destination, time, modelName);

    if (!shuttle.isValid()) {
        return false;
    }

    return shuttles.add(shuttle);
}
