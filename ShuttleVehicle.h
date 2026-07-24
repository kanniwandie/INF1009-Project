/**
 * @file ShuttleVehicle.h
 * @brief Declares the shuttle vehicle entity used for route scheduling.
 * @author Chen Xiyuan
 */
#ifndef SHUTTLE_VEHICLE_H
#define SHUTTLE_VEHICLE_H

#include "DriverlessVehicle.h"
#include "ShuttleModel.h"
#include "VehicleID.h"
#include <memory>
#include <string>
using namespace std;

/**
 * @brief Represents a shuttle vehicle with a model, ID, and assignment state.
 * @author Chen Xiyuan
 */
class ShuttleVehicle : public DriverlessVehicle {
private:
    VehicleID vehicleId;
    unique_ptr<ShuttleModel> model;

public:
    // Copying is implemented via a model clone so the registry can store vehicles safely.
    ShuttleVehicle(const ShuttleVehicle& other);
    ShuttleVehicle& operator=(const ShuttleVehicle& other);
    explicit ShuttleVehicle(const DriverlessVehicle& shuttle, bool isAssigned = false);
    ShuttleVehicle(const string& id, const string& destination, const string& scheduledTime, bool isAssigned = false);
    ShuttleVehicle(ShuttleVehicle&&) = default;
    ShuttleVehicle& operator=(ShuttleVehicle&&) = default;

    void setVehicleId(const string& id);
    string getVehicleId() const;
    bool hasSameID(const VehicleID& other) const;
    bool hasSameID(const string& other) const;
    void edit(const string& newDestination, const string& newTime, unique_ptr<ShuttleModel> newModel);
    void setModel(unique_ptr<ShuttleModel> newModel);
    const ShuttleModel* getModel() const;
    bool isValid() const override;

    string getType() const override;
    string getDescription() const override;
};

#endif
