/**
 * @file Destination.cpp
 * @brief Implements the destination value object used by entities.
 * @author Chen Xiyuan
 */

#include "Destination.h"
#include <cctype>

Destination::Destination(const string& initialValue) : value(initialValue) {}

void Destination::setValue(const string& newValue) {
    value = newValue;
}

bool Destination::isValid() const {
    if (value.empty()) {
        return false;
    }

    for (char ch : value) {
        if (!std::isalnum(static_cast<unsigned char>(ch)) && ch != ' ' && ch != '-' && ch != '_') {
            return false;
        }
    }
    return true;
}

string Destination::toString() const {
    return value;
}

Destination::operator string() const {
    return value;
}
