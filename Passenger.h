#ifndef PASSENGER_H
#define PASSENGER_H

#include "Entity.h"

class Passenger : public Entity {
private:
    bool isAssigned;

public:
    Passenger(const string& id, const string& destination, const string& scheduledTime, bool isAssigned = false);
    void setAssignedStatus(bool status);
    bool getAssignedStatus() const;
};

#endif