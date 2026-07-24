/**
 * @file DriverlessVehicle.h
 * @brief Defines the abstract vehicle base class for autonomous shuttles.
 * @author Chen Xiyuan
 */
#ifndef DRIVERLESS_VEHICLE_H
#define DRIVERLESS_VEHICLE_H

#include "Entity.h"
#include <string>
using namespace std;

/**
 * @brief Base class for autonomous vehicle entities.
 * @author Chen Xiyuan
 */
class DriverlessVehicle : public Entity {
public:
    DriverlessVehicle(const string& id, const string& destination, const string& scheduledTime);

    string getType() const override;
    string getDescription() const override;
};

#endif
