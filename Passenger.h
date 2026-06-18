#ifndef PASSENGER_H
#define PASSENGER_H

#include "Entity.h"
#include <string>
using namespace std;

class Passenger : public Entity {
private:
    bool isAssigned;

public:
    Passenger(const string& id, const string& destination, const string& scheduledTime, bool isAssigned = false);

    void setAssignedStatus(bool status);
    bool getAssignedStatus() const;

    string getType() const override;
    string getDescription() const override;
};

#endif
