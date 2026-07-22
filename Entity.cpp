#include "Entity.h"
using namespace std;

Entity::Entity(const string& id, const string& destination, const string& scheduledTime)
    : id(id), destination(destination), scheduledTime(make_unique<OperationalTime>()), assigned(false) {
    setDestination(destination);
    setScheduledTime(scheduledTime);
}

Entity::Entity(const Entity& other)
    : id(other.id), destination(other.destination), scheduledTime(nullptr), assigned(other.assigned) {
    if (other.scheduledTime) {
        scheduledTime = make_unique<OperationalTime>(other.scheduledTime->getHour(), other.scheduledTime->getMinute());
    }
}

Entity& Entity::operator=(const Entity& other) {
    if (this != &other) {
        id = other.id;
        destination = other.destination;
        assigned = other.assigned;
        if (other.scheduledTime) {
            scheduledTime = make_unique<OperationalTime>(other.scheduledTime->getHour(), other.scheduledTime->getMinute());
        } else {
            scheduledTime.reset();
        }
    }
    return *this;
}

void Entity::setDestination(const string& dest) {
    destination.setValue(dest);
}

void Entity::setScheduledTime(const string& time) {
    scheduledTime = OperationalTime::parse(time);
}

string Entity::getID() const { return id; }
string Entity::getDestination() const { return destination.toString(); }
string Entity::getScheduledTime() const { return scheduledTime ? scheduledTime->toString() : ""; }
const Destination& Entity::getDestinationObject() const { return destination; }
const Time& Entity::getScheduledTimeObject() const { return *scheduledTime; }

void Entity::setAssignedStatus(bool status) { assigned = status; }
bool Entity::getAssignedStatus() const { return assigned; }

string Entity::getDescription() const {
    return getType() + " " + id + " -> " + destination.toString() + " @ " + (scheduledTime ? scheduledTime->toString() : "");
}
