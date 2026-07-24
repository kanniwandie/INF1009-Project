/**
 * @file DataExporter.h
 * @brief Exports passenger and shuttle records into new data files.
 * @author Lee Yu Huan
 */
#ifndef DATA_EXPORTER_H
#define DATA_EXPORTER_H

#include <string>
using namespace std;

class PassengerList;
class ShuttleList;

/**
 * @brief Writes passenger and shuttle registries to output files in a structured format.
 * @author Lee Yu Huan
 */
class DataExporter {
public:
    bool savePassengers(const string& path, const PassengerList& passengers) const;
    bool saveShuttles(const string& path, const ShuttleList& shuttles) const;
};

#endif
