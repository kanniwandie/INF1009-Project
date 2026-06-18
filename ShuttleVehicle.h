#ifndef SHUTTLE_VEHICLE_H
#define SHUTTLE_VEHICLE_H

#include "DriverlessVehicle.h"
#include <string>
using namespace std;

class ShuttleVehicle : public DriverlessVehicle {
private:
    bool isAssigned;

public:
    ShuttleVehicle(const DriverlessVehicle& shuttle, bool isAssigned = false);
    ShuttleVehicle(const string& id, const string& destination, const string& scheduledTime, bool isAssigned = false);

    void setAssignedStatus(bool status);
    bool getAssignedStatus() const;

    string getType() const override;
    string getDescription() const override;
};

#endif
