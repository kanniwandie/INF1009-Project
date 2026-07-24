/**
 * @file Entity.h
 * @brief Defines the abstract base entity used by passengers and shuttles.
 * @author Chen Xiyuan
 */
#ifndef ENTITY_H
#define ENTITY_H

#include "Destination.h"
#include "OperationalTime.h"
#include "Time.h"
#include <memory>
#include <string>
using namespace std;

/**
 * @brief Abstract base class for all domain entities in the scheduling system.
 * @author Chen Xiyuan
 */
class Entity {
protected:
    string id;
    Destination destination;
    unique_ptr<Time> scheduledTime;
    bool assigned;

public:
    /**
     * @brief Constructs a new entity with an identifier, destination, and scheduled time.
     * @param id Unique identifier for the entity.
     * @param destination Destination associated with the entity.
     * @param scheduledTime Initial scheduled time supplied as a string.
     */
    Entity(const string& id, const string& destination, const string& scheduledTime);

    /**
     * @brief Destroys the entity instance.
     */
    virtual ~Entity() = default;

    /**
     * @brief Copies the state of another entity.
     * @param other The entity to copy from.
     */
    Entity(const Entity& other);

    /**
     * @brief Assigns this entity the state of another entity.
     * @param other The entity to copy from.
     * @return Reference to this entity.
     */
    Entity& operator=(const Entity& other);

    /**
     * @brief Updates the entity destination.
     * @param dest New destination value.
     */
    void setDestination(const string& dest);

    /**
     * @brief Updates the entity scheduled time.
     * @param time New time value supplied as input text.
     */
    void setScheduledTime(const string& time);

    /**
     * @brief Retrieves the entity identifier.
     * @return Identifier string.
     */
    string getID() const;

    /**
     * @brief Retrieves the destination as a string.
     * @return Destination string.
     */
    string getDestination() const;

    /**
     * @brief Retrieves the scheduled time as a formatted string.
     * @return Scheduled time string.
     */
    string getScheduledTime() const;

    /**
     * @brief Retrieves the destination value object.
     * @return Constant reference to the destination value object.
     */
    const Destination& getDestinationObject() const;

    /**
     * @brief Retrieves the scheduled time object.
     * @return Constant reference to the scheduled time object.
     */
    const Time& getScheduledTimeObject() const;

    /**
     * @brief Updates the assignment state for the entity.
     * @param status The new assignment state.
     */
    virtual void setAssignedStatus(bool status);

    /**
     * @brief Reports whether the entity is currently assigned.
     * @return True when assigned, otherwise false.
     */
    virtual bool getAssignedStatus() const;

    /**
     * @brief Checks whether the entity data is valid.
     * @return True when the entity satisfies the domain rules.
     */
    virtual bool isValid() const = 0;

    /**
     * @brief Returns the runtime type name of the entity.
     * @return Polymorphic type label.
     */
    virtual string getType() const = 0;

    /**
     * @brief Returns a human-readable description of the entity.
     * @return Description string.
     */
    virtual string getDescription() const;
};

#endif
