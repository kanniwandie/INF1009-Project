/**
 * @file SystemDataService.h
 * @brief Offers service-level data operations for loading, editing, and exporting system data.
 * @author Lee Yu Huan
 */
#ifndef SYSTEM_DATA_SERVICE_H
#define SYSTEM_DATA_SERVICE_H

#include "Registry.h"
#include "DataExporter.h"
#include <string>
using namespace std;

// Reports each data file's load status independently. A single bool return here
// previously meant a partial load (e.g. only passenger.txt present) either silently
// looked like full success (old "||" behavior) or falsely looked like total failure
// (old "&&" behavior) even when one file's data loaded and is genuinely usable.
/**
 * @brief Reports the outcome of loading passenger and shuttle data files.
 * @author Lee Yu Huan
 */
struct LoadResult {
    bool passengerLoaded = false;
    bool shuttleLoaded = false;
    bool allLoaded() const { return passengerLoaded && shuttleLoaded; }
    bool anyLoaded() const { return passengerLoaded || shuttleLoaded; }
};

/**
 * @brief Service class that coordinates data loading, editing, and export workflows.
 * @author Lee Yu Huan
 */
class SystemDataService {
private:
    DataExporter exporter;

public:
    static LoadResult loadInitialData(PassengerList& passengers, ShuttleList& shuttles, const string& folder = "");

    bool editPassenger(PassengerList& passengers, const string& id, const string& newDestination, const string& newTime, int newGroupSize) const;
    bool editShuttle(ShuttleList& shuttles, const string& id, const string& newDestination, const string& newTime, const string& newModel) const;
    bool savePassengerData(const string& path, const PassengerList& passengers) const;
    bool saveShuttleData(const string& path, const ShuttleList& shuttles) const;
};

#endif
