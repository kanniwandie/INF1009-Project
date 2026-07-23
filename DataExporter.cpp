#include "DataExporter.h"
#include "Registry.h"
#include "Passenger.h"
#include "ShuttleVehicle.h"
#include <fstream>
#include <filesystem>

bool DataExporter::savePassengers(const string& path, const PassengerList& passengers) const {
    if (path.empty() || std::filesystem::exists(path)) {
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
    if (path.empty() || std::filesystem::exists(path)) {
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