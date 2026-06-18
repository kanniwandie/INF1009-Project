#ifndef SHUTTLE_VEHICLES_H
#define SHUTTLE_VEHICLES_H

#include "DriverlessVehicle.h"

class ShuttleVehicle : public DriverlessVehicle {
private:
    bool isAssigned;

public:
    ShuttleVehicle(const DriverlessVehicle& shuttle, bool isAssigned = false);
    ShuttleVehicle(const string& id, const string& destination, const string& scheduledTime, bool isAssigned = false);

    void setAssignedStatus(bool status);
    bool getAssignedStatus() const;
};

#endif