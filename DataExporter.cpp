/**
 * @file DataExporter.cpp
 * @brief Implements exporting of passenger and shuttle data into text files.
 * @author Lee Yu Huan
 */
#include "DataExporter.h"
#include "Registry.h"
#include "Passenger.h"
#include "ShuttleVehicle.h"
#include <fstream>

namespace {
bool fileExists(const string& path) {
    // Check whether a target export path already exists before writing a new file.
    ifstream input(path.c_str());
    return input.good();
}
}

bool DataExporter::savePassengers(const string& path, const PassengerList& passengers) const {
    // Export the current passenger registry to a new text file without overwriting existing data.
    if (path.empty() || fileExists(path)) {
        return false;
    }

    ofstream file(path);

    if (!file.is_open()) {
        return false;
    }

    for (const auto& passenger : passengers.getItems()) {
        file << passenger.getID() << ","
             << passenger.getDestination() << ","
             << passenger.getScheduledTime() << ","
             << passenger.getGroupSize() << "\n";
    }

    return file.good();
}

bool DataExporter::saveShuttles(const string& path, const ShuttleList& shuttles) const {
    // Export the current shuttle registry to a new text file using the shuttle model code.
    if (path.empty() || fileExists(path)) {
        return false;
    }

    ofstream file(path);

    if (!file.is_open()) {
        return false;
    }

    for (const auto& shuttle : shuttles.getItems()) {
        const string modelCode =
            shuttle.getModel()
                ? shuttle.getModel()->getCode()
                : "Small";

        file << shuttle.getID() << ","
             << shuttle.getDestination() << ","
             << shuttle.getScheduledTime() << ","
             << modelCode << "\n";
    }

    return file.good();
}