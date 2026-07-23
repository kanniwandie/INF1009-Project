#include "DataExporter.h"
#include "Registry.h"
#include "Passenger.h"
#include "ShuttleVehicle.h"
#include <fstream>

bool DataExporter::savePassengers(const string& path, const PassengerList& passengers) const {
    ofstream file(path);
    if (!file.is_open()) {
        return false;
    }

    for (const auto& passenger : passengers.getItems()) {
        file << passenger.getID() << "," << passenger.getDestination() << "," << passenger.getScheduledTime() << "," << passenger.getGroupSize() << "\n";
    }
    return true;
}

bool DataExporter::saveShuttles(const string& path, const ShuttleList& shuttles) const {
    ofstream file(path);
    if (!file.is_open()) {
        return false;
    }

    for (const auto& shuttle : shuttles.getItems()) {
        const string modelCode = shuttle.getModel() ? shuttle.getModel()->getCode() : "Small";
        file << shuttle.getID() << "," << shuttle.getDestination() << "," << shuttle.getScheduledTime() << "," << modelCode << "\n";
    }
    return true;
}
