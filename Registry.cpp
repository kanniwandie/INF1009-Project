#include "Registry.h"
#include "Passenger.h"
#include "ShuttleVehicle.h"
using namespace std;

// ---- PassengerList: forwards to its composed Registry<Passenger> ----
bool PassengerList::add(const Passenger& item) { return registry.add(item); }
bool PassengerList::remove(const string& id) { return registry.remove(id); }
bool PassengerList::containsId(const string& id) const { return registry.containsId(id); }
const vector<Passenger>& PassengerList::getItems() const { return registry.getItems(); }
Passenger* PassengerList::findById(const string& id) { return registry.findById(id); }
const Passenger* PassengerList::findById(const string& id) const { return registry.findById(id); }
size_t PassengerList::size() const { return registry.size(); }
Passenger& PassengerList::operator[](size_t index) { return registry[index]; }
const Passenger& PassengerList::operator[](size_t index) const { return registry[index]; }
void PassengerList::clear() { registry.clear(); }
void PassengerList::resetAssignments() { registry.resetAssignments(); }

// ---- ShuttleList: forwards to its composed Registry<ShuttleVehicle> ----
bool ShuttleList::add(const ShuttleVehicle& item) { return registry.add(item); }
bool ShuttleList::remove(const string& id) { return registry.remove(id); }
bool ShuttleList::containsId(const string& id) const { return registry.containsId(id); }
const vector<ShuttleVehicle>& ShuttleList::getItems() const { return registry.getItems(); }
ShuttleVehicle* ShuttleList::findById(const string& id) { return registry.findById(id); }
const ShuttleVehicle* ShuttleList::findById(const string& id) const { return registry.findById(id); }
size_t ShuttleList::size() const { return registry.size(); }
ShuttleVehicle& ShuttleList::operator[](size_t index) { return registry[index]; }
const ShuttleVehicle& ShuttleList::operator[](size_t index) const { return registry[index]; }
void ShuttleList::clear() { registry.clear(); }
void ShuttleList::resetAssignments() { registry.resetAssignments(); }
