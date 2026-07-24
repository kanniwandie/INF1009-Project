/**
 * @file FileLoader.h
 * @brief Defines the file-loading and parsing abstractions for passenger and shuttle data.
 * @author Lee Yu Huan
 */
#ifndef FILE_LOADER_H
#define FILE_LOADER_H

#include <string>
#include <vector>
using namespace std;

class Passenger;
class ShuttleVehicle;
class PassengerList;
class ShuttleList;

/**
 * @brief Abstract input loader used by the parser layer.
 * @author Lee Yu Huan
 */
class FileLoader {
public:
    virtual ~FileLoader() = default;
    virtual bool load(const string& path, PassengerList& passengers, ShuttleList& shuttles) = 0;
};

/**
 * @brief Parses passenger rows from file input into Passenger objects.
 * @author Lee Yu Huan
 */
class PassengerParser : public FileLoader {
public:
    bool load(const string& path, PassengerList& passengers, ShuttleList& shuttles) override;
    bool parse(const string& rawEntry, PassengerList& passengers, ShuttleList& shuttles) const;
};

/**
 * @brief Parses shuttle rows from file input into ShuttleVehicle objects.
 * @author Lee Yu Huan
 */
class ShuttleParser : public FileLoader {
public:
    bool load(const string& path, PassengerList& passengers, ShuttleList& shuttles) override;
    bool parse(const string& rawEntry, PassengerList& passengers, ShuttleList& shuttles) const;
};

#endif
