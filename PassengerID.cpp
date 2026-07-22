#include "PassengerID.h"
#include <algorithm>
#include <cctype>

PassengerID::PassengerID(const string& rawValue) : value(rawValue) {}

bool PassengerID::isValid() const {
    if (value.empty()) {
        return false;
    }

    return all_of(value.begin(), value.end(), [](unsigned char ch) {
        return isalnum(ch);
    });
}

string PassengerID::getValue() const {
    return value;
}

bool PassengerID::operator==(const PassengerID& other) const {
    return value == other.value;
}

bool PassengerID::operator==(const string& other) const {
    return value == other;
}
