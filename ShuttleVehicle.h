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
    /**
     * @brief Copies a shuttle vehicle by cloning its model.
     * @param other Shuttle vehicle to copy from.
     */
    ShuttleVehicle(const ShuttleVehicle& other);

    /**
     * @brief Assigns this shuttle vehicle the state of another shuttle.
     * @param other Shuttle vehicle to copy from.
     * @return Reference to this shuttle vehicle.
     */
    ShuttleVehicle& operator=(const ShuttleVehicle& other);

    /**
     * @brief Constructs a shuttle vehicle from a driverless vehicle base object.
     * @param shuttle Base vehicle data to copy.
     * @param isAssigned Initial assignment state.
     */
    explicit ShuttleVehicle(const DriverlessVehicle& shuttle, bool isAssigned = false);

    /**
     * @brief Constructs a shuttle vehicle with a custom identifier, destination, and time.
     * @param id Vehicle identifier.
     * @param destination Destination for the shuttle.
     * @param scheduledTime Scheduled time.
     * @param isAssigned Initial assignment state.
     */
    ShuttleVehicle(const string& id, const string& destination, const string& scheduledTime, bool isAssigned = false);
    ShuttleVehicle(ShuttleVehicle&&) = default;
    ShuttleVehicle& operator=(ShuttleVehicle&&) = default;

    /**
     * @brief Updates the shuttle vehicle identifier.
     * @param id New vehicle identifier.
     */
    void setVehicleId(const string& id);

    /**
     * @brief Retrieves the shuttle vehicle identifier.
     * @return Vehicle identifier string.
     */
    string getVehicleId() const;

    /**
     * @brief Compares this vehicle identifier with another vehicle identifier object.
     * @param other Identifier to compare against.
     * @return True when both identifiers match.
     */
    bool hasSameID(const VehicleID& other) const;

    /**
     * @brief Compares this vehicle identifier with a string identifier.
     * @param other Identifier text to compare against.
     * @return True when both identifiers match.
     */
    bool hasSameID(const string& other) const;

    /**
     * @brief Edits the shuttle destination, time, and model in one operation.
     * @param newDestination Updated destination.
     * @param newTime Updated scheduled time.
     * @param newModel New shuttle model.
     */
    void edit(const string& newDestination, const string& newTime, unique_ptr<ShuttleModel> newModel);

    /**
     * @brief Replaces the shuttle model used by the vehicle.
     * @param newModel New shuttle model implementation.
     */
    void setModel(unique_ptr<ShuttleModel> newModel);

    /**
     * @brief Retrieves the current shuttle model.
     * @return Pointer to the current shuttle model.
     */
    const ShuttleModel* getModel() const;

    /**
     * @brief Validates the shuttle vehicle against the domain rules.
     * @return True when the shuttle is valid.
     */
    bool isValid() const override;

    /**
     * @brief Returns the runtime type label for the shuttle vehicle.
     * @return "ShuttleVehicle".
     */
    string getType() const override;

    /**
     * @brief Returns a human-readable description of the shuttle vehicle.
     * @return Description string.
     */
    string getDescription() const override;
};

#endif
