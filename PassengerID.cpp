/**
 * @file PassengerID.h
 * @brief Declares the passenger ID value object.
 * @author Chen Xiyuan
 */
/**
 * @file PassengerID.cpp
 * @brief Implements the passenger ID value object.
 * @author Chen Xiyuan
 */

#include "PassengerID.h"
#include <algorithm>
#include <cctype>

PassengerID::PassengerID(const string& rawValue) : value(rawValue) {}

bool PassengerID::isValid() const {
    // Ensure the identifier contains only alphanumeric characters and is not empty.
    if (value.empty()) {
        return false;
    }

    return all_of(value.begin(), value.end(), [](unsigned char ch) {
        return isalnum(ch);
    });
}

string PassengerID::getValue() const {
    // Return the raw identifier string for display or comparison.
    return value;
}

bool PassengerID::operator==(const PassengerID& other) const {
    return value == other.value;
}

bool PassengerID::operator==(const string& other) const {
    return value == other;
}
