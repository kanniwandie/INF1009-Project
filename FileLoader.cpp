/**
 * @file FileLoader.cpp
 * @brief Implements file parsing and validation for passenger and shuttle input.
 * @author Lee Yu Huan
 */
#include "FileLoader.h"
#include "Registry.h"
#include "Passenger.h"
#include "ShuttleVehicle.h"
#include "ShuttleModel.h"
#include "OperationalTime.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <utility>
#include <vector>

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
struct ValidationIssue {
    string reason;
    string detail;
};

ValidationIssue inspectPassengerEntry(const string& rawEntry, const PassengerList& passengers) {
    stringstream ss(rawEntry);
    string id, destination, time, groupSizeField;
    if (!getline(ss, id, ',') || !getline(ss, destination, ',') || !getline(ss, time, ',') || !getline(ss, groupSizeField, ',')) {
        return {"malformed", "expected 4 comma-separated fields"};
    }

    string cleanedId = trim(id);
    string cleanedDestination = trim(destination);
    string cleanedTime = trim(time);
    string cleanedGroupSize = trim(groupSizeField);

    if (cleanedId.empty()) {
        return {"invalid", "missing passenger ID"};
    }

    if (cleanedDestination.empty()) {
        return {"invalid", "missing destination"};
    }

    if (cleanedTime.empty()) {
        return {"invalid", "missing time"};
    }

    if (cleanedGroupSize.empty()) {
        return {"invalid", "missing group size"};
    }

    int groupSize = -1;
    try {
        size_t processedCharacters = 0;
        int parsedGroupSize = stoi(cleanedGroupSize, &processedCharacters);
        if (processedCharacters == cleanedGroupSize.size()) {
            groupSize = parsedGroupSize;
        }
    } catch (...) {
        groupSize = -1;
    }

    if (groupSize < 1 || groupSize > 15) {
        return {"invalid", "group size must be between 1 and 15"};
    }

    auto parsedTime = OperationalTime::parse(cleanedTime);
    if (!parsedTime || !parsedTime->isValid()) {
        return {"out-of-window", "time is outside the allowed operational window (06:00am to 00:00am)"};
    }

    if (passengers.containsId(cleanedId)) {
        return {"duplicate", "passenger ID already exists"};
    }

    return {"", ""};
}

ValidationIssue inspectShuttleEntry(const string& rawEntry, const ShuttleList& shuttles) {
    stringstream ss(rawEntry);
    string id, destination, time, modelName;
    if (!getline(ss, id, ',') || !getline(ss, destination, ',') || !getline(ss, time, ',') || !getline(ss, modelName, ',')) {
        return {"malformed", "expected 4 comma-separated fields"};
    }

    string cleanedId = trim(id);
    string cleanedDestination = trim(destination);
    string cleanedTime = trim(time);
    string cleanedModel = normalizeModel(trim(modelName));

    if (cleanedId.empty()) {
        return {"invalid", "missing shuttle ID"};
    }

    if (cleanedDestination.empty()) {
        return {"invalid", "missing charging point"};
    }

    if (cleanedTime.empty()) {
        return {"invalid", "missing time"};
    }

    if (cleanedModel.empty()) {
        return {"invalid", "model must be Small, Family, or Premium"};
    }

    auto parsedTime = OperationalTime::parse(cleanedTime);
    if (!parsedTime || !parsedTime->isValid()) {
        return {"out-of-window", "time is outside the allowed operational window (06:00am to 00:00am)"};
    }

    if (shuttles.containsId(cleanedId)) {
        return {"duplicate", "shuttle ID already exists"};
    }

    return {"", ""};
}

Passenger createPassengerFromFields(const string& id, const string& destination, const string& time, const string& groupSizeField) {
    int groupSize = -1;
    string cleanedGroupSize = trim(groupSizeField);

    try {
        size_t processedCharacters = 0;
        int parsedGroupSize = stoi(cleanedGroupSize, &processedCharacters);
        if (processedCharacters == cleanedGroupSize.size()) {
            groupSize = parsedGroupSize;
        }
    }
    catch (...) {
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
    vector<string> skippedOutsideOperationalWindow;
    while (getline(file, line)) {
        ++lineNumber;
        if (trim(line).empty()) continue;
        if (!parse(line, passengers, shuttles)) {
            const auto issue = inspectPassengerEntry(line, passengers);
            if (issue.reason == "out-of-window") {
                skippedOutsideOperationalWindow.push_back(line);
            }

            cout << "[Warning] " << path << " line " << lineNumber << " -> "
                 << issue.reason << ": " << issue.detail << " (entry skipped)\n";
            cout << "  Entry: " << line << "\n";
        }
    }

    if (!skippedOutsideOperationalWindow.empty()) {
        cout << "[Operational Window] Passenger entries skipped because their time was outside the allowed window (06:00am to 00:00am):\n";
        for (const string& skipped : skippedOutsideOperationalWindow) {
            cout << "  - " << skipped << "\n";
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
    vector<string> skippedOutsideOperationalWindow;
    while (getline(file, line)) {
        ++lineNumber;
        if (trim(line).empty()) continue;
        if (!parse(line, passengers, shuttles)) {
            const auto issue = inspectShuttleEntry(line, shuttles);
            if (issue.reason == "out-of-window") {
                skippedOutsideOperationalWindow.push_back(line);
            }

            cout << "[Warning] " << path << " line " << lineNumber << " -> "
                 << issue.reason << ": " << issue.detail << " (entry skipped)\n";
            cout << "  Entry: " << line << "\n";
        }
    }

    if (!skippedOutsideOperationalWindow.empty()) {
        cout << "[Operational Window] Shuttle entries skipped because their time was outside the allowed window (06:00am to 00:00am):\n";
        for (const string& skipped : skippedOutsideOperationalWindow) {
            cout << "  - " << skipped << "\n";
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
