#ifndef DRIVERLESS_VEHICLES_H
#define DRIVERLESS_VEHICLES_H

#include "Entity.h"

using namespace std;

class DriverlessVehicle : public Entity {
public:
    DriverlessVehicle(const string& id, const string& destination, const string& scheduledTime);
};

#endif
