#include "VehicleID.h"
#include <algorithm>
#include <cctype>

VehicleID::VehicleID(const string& rawValue) : value(rawValue) {}

bool VehicleID::isValid() const {
    if (value.empty()) {
        return false;
    }

    return all_of(value.begin(), value.end(), [](unsigned char ch) {
        return isalnum(ch);
    });
}

string VehicleID::getValue() const {
    return value;
}

bool VehicleID::operator==(const VehicleID& other) const {
    return value == other.value;
}

bool VehicleID::operator==(const string& other) const {
    return value == other;
}
