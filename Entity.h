#ifndef ENTITY_H
#define ENTITY_H

#include <string>
using namespace std;

class Entity {
protected:
    string id;
    string destination;
    string scheduledTime;

public:
    Entity(const string& id, const string& destination, const string& scheduledTime);
    virtual ~Entity() = default;
    Entity(const Entity& other) = default;
    Entity& operator=(const Entity& other) = default;

    void setDestination(const string& dest);
    void setScheduledTime(const string& time);

    string getID() const;
    string getDestination() const;
    string getScheduledTime() const;

    virtual string getType() const = 0;
    virtual string getDescription() const;
};

#endif
