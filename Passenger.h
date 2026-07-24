/**
 * @file Passenger.h
 * @brief Defines the passenger entity and its behaviour within the scheduling system.
 * @author Chen Xiyuan
 */
#ifndef PASSENGER_H
#define PASSENGER_H

#include "Entity.h"
#include "PassengerID.h"
#include <string>
using namespace std;

/**
 * @brief Represents a passenger request with destination, time, and group-size information.
 * @author Chen Xiyuan
 */
class Passenger : public Entity {
private:
    PassengerID passengerId;
    int groupSize;

public:
    /**
     * @brief Constructs a passenger with an identifier, destination, time, and group size.
     * @param id Passenger identifier.
     * @param destination Passenger destination.
     * @param scheduledTime Staff-assigned pickup time.
     * @param groupSize Number of passengers in the group.
     * @param isAssigned Initial assignment state.
     */
    Passenger(const string& id, const string& destination, const string& scheduledTime, int groupSize = 1, bool isAssigned = false);

    /**
     * @brief Updates the passenger group size.
     * @param size New group size.
     */
    void setGroupSize(int size);

    /**
     * @brief Retrieves the passenger group size.
     * @return Number of passengers in the group.
     */
    int getGroupSize() const;

    /**
     * @brief Validates the passenger object against the domain rules.
     * @return True when the passenger is valid.
     */
    bool isValid() const override;

    /**
     * @brief Compares this passenger identifier with another passenger identifier value object.
     * @param other Identifier to compare against.
     * @return True when both identifiers match.
     */
    bool hasSameID(const PassengerID& other) const;

    /**
     * @brief Compares this passenger identifier with a string identifier.
     * @param other Identifier text to compare against.
     * @return True when both identifiers match.
     */
    bool hasSameID(const string& other) const;

    /**
     * @brief Edits the passenger's destination, time, and group size in one operation.
     * @param newDestination Updated destination.
     * @param newTime Updated scheduled time.
     * @param newGroupSize Updated group size.
     */
    void edit(const string& newDestination, const string& newTime, int newGroupSize);

    /**
     * @brief Returns the runtime type label for the passenger.
     * @return "Passenger".
     */
    string getType() const override;

    /**
     * @brief Returns a human-readable description of the passenger.
     * @return Description string.
     */
    string getDescription() const override;
};

#endif
