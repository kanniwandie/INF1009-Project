#include "Entity.h"
using namespace std;

Entity::Entity(const string& id, const string& destination, const string& scheduledTime)
    : id(id), destination(destination), scheduledTime(scheduledTime) {
}

void Entity::setDestination(const string& dest) { destination = dest; }
void Entity::setScheduledTime(const string& time) { scheduledTime = time; }

string Entity::getID() const { return id; }
string Entity::getDestination() const { return destination; }
string Entity::getScheduledTime() const { return scheduledTime; }

string Entity::getDescription() const {
    return getType() + " " + id + " -> " + destination + " @ " + scheduledTime;
}
