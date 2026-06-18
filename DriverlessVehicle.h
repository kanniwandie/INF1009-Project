#ifndef DRIVERLESS_VEHICLE_H
#define DRIVERLESS_VEHICLE_H

#include "Entity.h"
#include <string>
using namespace std;

class DriverlessVehicle : public Entity {
public:
    DriverlessVehicle(const string& id, const string& destination, const string& scheduledTime);

    string getType() const override;
    string getDescription() const override;
};

#endif
