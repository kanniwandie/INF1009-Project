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
    /**
     * @brief Constructs a driverless vehicle entity.
     * @param id Vehicle identifier.
     * @param destination Vehicle destination.
     * @param scheduledTime Scheduled departure time.
     */
    DriverlessVehicle(const string& id, const string& destination, const string& scheduledTime);

    /**
     * @brief Returns the runtime type label for the driverless vehicle.
     * @return "DriverlessVehicle".
     */
    string getType() const override;

    /**
     * @brief Returns a human-readable description of the driverless vehicle.
     * @return Description string.
     */
    string getDescription() const override;
};

#endif
