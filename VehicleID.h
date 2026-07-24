/**
 * @file VehicleID.h
 * @brief Declares the shuttle vehicle ID value object.
 * @author Chen Xiyuan
 */
#ifndef VEHICLE_ID_H
#define VEHICLE_ID_H

#include <string>
using namespace std;

/**
 * @brief Strongly typed identifier for shuttle vehicles.
 * @author Chen Xiyuan
 */
class VehicleID {
private:
    string value;

public:
    explicit VehicleID(const string& rawValue = "");

    bool isValid() const;
    string getValue() const;
    bool operator==(const VehicleID& other) const;
    bool operator==(const string& other) const;
};

#endif
