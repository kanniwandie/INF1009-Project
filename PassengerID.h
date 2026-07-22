#ifndef PASSENGER_ID_H
#define PASSENGER_ID_H

#include <string>
using namespace std;

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
