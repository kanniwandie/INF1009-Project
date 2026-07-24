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
    Entity(const string& id, const string& destination, const string& scheduledTime);
    virtual ~Entity() = default;
    Entity(const Entity& other);
    Entity& operator=(const Entity& other);

    void setDestination(const string& dest);
    void setScheduledTime(const string& time);

    string getID() const;
    string getDestination() const;
    string getScheduledTime() const;
    const Destination& getDestinationObject() const;
    const Time& getScheduledTimeObject() const;

    virtual void setAssignedStatus(bool status);
    virtual bool getAssignedStatus() const;
    virtual bool isValid() const = 0;
    virtual string getType() const = 0;
    virtual string getDescription() const;
};

#endif
