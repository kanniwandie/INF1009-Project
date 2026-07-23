#ifndef SYSTEM_DATA_SERVICE_H
#define SYSTEM_DATA_SERVICE_H

#include "Registry.h"
#include "DataExporter.h"
#include <string>
using namespace std;

// Author: [Your Name]
class SystemDataService {
private:
    DataExporter exporter;

public:
    static bool loadInitialData(PassengerList& passengers, ShuttleList& shuttles, const string& folder = "");

    bool editPassenger(PassengerList& passengers, const string& id, const string& newDestination, const string& newTime, int newGroupSize) const;
    bool editShuttle(ShuttleList& shuttles, const string& id, const string& newDestination, const string& newTime, const string& newModel) const;
    bool savePassengerData(const string& path, const PassengerList& passengers) const;
    bool saveShuttleData(const string& path, const ShuttleList& shuttles) const;
};

#endif
