#include "SystemDataService.h"
#include "FileLoader.h"
#include "Passenger.h"
#include "ShuttleVehicle.h"
#include "ShuttleModel.h"
#include <fstream>
#include <iostream>
#include <memory>

namespace {
string buildPath(const string& folder, const string& filename) {
    if (folder.empty()) return filename;
    return folder.back() == '/' || folder.back() == '\\' ? folder + filename : folder + "/" + filename;
}
}

LoadResult SystemDataService::loadInitialData(PassengerList& passengers, ShuttleList& shuttles, const string& folder) {
    passengers.clear();
    shuttles.clear();

    PassengerParser passengerParser;
    ShuttleParser shuttleParser;

    LoadResult result;
    result.passengerLoaded = passengerParser.load(buildPath(folder, "passenger.txt"), passengers, shuttles);
    result.shuttleLoaded = shuttleParser.load(buildPath(folder, "shuttle.txt"), passengers, shuttles);
    return result;
}

bool SystemDataService::editPassenger(PassengerList& passengers, const string& id, const string& newDestination, const string& newTime, int newGroupSize) const {
    Passenger* passenger = passengers.findById(id);
    if (!passenger) {
        return false;
    }

    passenger->edit(newDestination, newTime, newGroupSize);
    passengers.resetAssignments();
    return true;
}

bool SystemDataService::editShuttle(ShuttleList& shuttles, const string& id, const string& newDestination, const string& newTime, const string& newModel) const {
    ShuttleVehicle* shuttle = shuttles.findById(id);
    if (!shuttle) {
        return false;
    }

    unique_ptr<ShuttleModel> model;
    if (newModel == "Family") {
        model = make_unique<FamilyShuttleModel>();
    } else if (newModel == "Premium") {
        model = make_unique<PremiumShuttleModel>();
    } else {
        model = make_unique<SmallShuttleModel>();
    }

    shuttle->edit(newDestination, newTime, std::move(model));
    shuttles.resetAssignments();
    return true;
}

bool SystemDataService::savePassengerData(const string& path, const PassengerList& passengers) const {
    return exporter.savePassengers(path, passengers);
}

bool SystemDataService::saveShuttleData(const string& path, const ShuttleList& shuttles) const {
    return exporter.saveShuttles(path, shuttles);
}
