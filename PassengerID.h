/**
 * @file PassengerID.h
 * @brief Declares the passenger ID value object.
 * @author Chen Xiyuan
 */
#ifndef PASSENGER_ID_H
#define PASSENGER_ID_H

#include <string>
using namespace std;

/**
 * @brief Strongly typed passenger identifier used for validation and comparison.
 * @author Chen Xiyuan
 */
class PassengerID {
private:
    string value;

public:
    explicit PassengerID(const string& rawValue = "");

    bool isValid() const;
    string getValue() const;
    bool operator==(const PassengerID& other) const;
    bool operator==(const string& other) const;
};

#endif
