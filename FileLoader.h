#ifndef FILE_LOADER_H
#define FILE_LOADER_H

#include <string>
#include <vector>
using namespace std;

class Passenger;
class ShuttleVehicle;
class PassengerList;
class ShuttleList;

class FileLoader {
public:
    virtual ~FileLoader() = default;
    virtual bool load(const string& path, PassengerList& passengers, ShuttleList& shuttles) = 0;
};

class PassengerParser : public FileLoader {
public:
    bool load(const string& path, PassengerList& passengers, ShuttleList& shuttles) override;
    bool parse(const string& rawEntry, PassengerList& passengers, ShuttleList& shuttles) const;
};

class ShuttleParser : public FileLoader {
public:
    bool load(const string& path, PassengerList& passengers, ShuttleList& shuttles) override;
    bool parse(const string& rawEntry, PassengerList& passengers, ShuttleList& shuttles) const;
};

#endif
