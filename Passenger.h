#ifndef PASSENGER_H
#define PASSENGER_H

#include "Entity.h"
#include "PassengerID.h"
#include <string>
using namespace std;

class Passenger : public Entity {
private:
    PassengerID passengerId;
    int groupSize;

public:
    Passenger(const string& id, const string& destination, const string& scheduledTime, int groupSize = 1, bool isAssigned = false);

    void setGroupSize(int size);
    int getGroupSize() const;
    bool isValid() const override;
    bool hasSameID(const PassengerID& other) const;
    bool hasSameID(const string& other) const;
    void edit(const string& newDestination, const string& newTime, int newGroupSize);

    string getType() const override;
    string getDescription() const override;
};

#endif
