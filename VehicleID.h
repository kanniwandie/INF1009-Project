#ifndef VEHICLE_ID_H
#define VEHICLE_ID_H

#include <string>
using namespace std;

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
