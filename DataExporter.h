#ifndef DATA_EXPORTER_H
#define DATA_EXPORTER_H

#include <string>
using namespace std;

class PassengerList;
class ShuttleList;

class DataExporter {
public:
    bool savePassengers(const string& path, const PassengerList& passengers) const;
    bool saveShuttles(const string& path, const ShuttleList& shuttles) const;
};

#endif
