#ifndef REGISTRY_H
#define REGISTRY_H

#include <vector>
#include <string>
using namespace std;

class Passenger;
class ShuttleVehicle;

// Purpose: Generic in-memory store keyed by string ID. Kept deliberately generic and
// domain-agnostic - it knows nothing about passengers or shuttles specifically, only
// that T has getID()/setAssignedStatus(). PassengerList/ShuttleList below compose one
// of these rather than inheriting from it (see the note on those classes).
template <typename T>
class Registry {
private:
    vector<T> items;

public:
    Registry() = default;
    ~Registry() = default;
    Registry(const Registry& other) = default;
    Registry& operator=(const Registry& other) = default;

    bool add(const T& item) {
        if (containsId(item.getID())) {
            return false;
        }
        items.push_back(item);
        return true;
    }

    bool remove(const string& id) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->getID() == id) {
                items.erase(it);
                return true;
            }
        }
        return false;
    }

    bool containsId(const string& id) const {
        return findById(id) != nullptr;
    }

    const vector<T>& getItems() const {
        return items;
    }

    T* findById(const string& id) {
        for (auto& item : items) {
            if (item.getID() == id) return &item;
        }
        return nullptr;
    }

    const T* findById(const string& id) const {
        for (const auto& item : items) {
            if (item.getID() == id) return &item;
        }
        return nullptr;
    }

    size_t size() const { return items.size(); }

    T& operator[](size_t index) { return items[index]; }
    const T& operator[](size_t index) const { return items[index]; }

    void clear() { items.clear(); }

    void resetAssignments() {
        for (auto& item : items) {
            item.setAssignedStatus(false);
        }
    }
};

// Purpose: The town's passenger roster. Composes a Registry<Passenger> (HAS-A) instead
// of inheriting from it (IS-A). A PassengerList is a domain concept in its own right -
// it is not, conceptually, "a kind of generic registry that happens to hold passengers".
// Composition also means PassengerList is free to grow domain-specific behaviour later
// without that behaviour leaking into the generic Registry template, and without a
// consumer of PassengerList being able to slice it down to a bare Registry<Passenger>.
class PassengerList {
private:
    Registry<Passenger> registry;

public:
    bool add(const Passenger& item);
    bool remove(const string& id);
    bool containsId(const string& id) const;
    const vector<Passenger>& getItems() const;
    Passenger* findById(const string& id);
    const Passenger* findById(const string& id) const;
    size_t size() const;
    Passenger& operator[](size_t index);
    const Passenger& operator[](size_t index) const;
    void clear();
    void resetAssignments();
};

// Purpose: The town's shuttle roster. See PassengerList above for the composition
// rationale - the same reasoning applies here.
class ShuttleList {
private:
    Registry<ShuttleVehicle> registry;

public:
    bool add(const ShuttleVehicle& item);
    bool remove(const string& id);
    bool containsId(const string& id) const;
    const vector<ShuttleVehicle>& getItems() const;
    ShuttleVehicle* findById(const string& id);
    const ShuttleVehicle* findById(const string& id) const;
    size_t size() const;
    ShuttleVehicle& operator[](size_t index);
    const ShuttleVehicle& operator[](size_t index) const;
    void clear();
    void resetAssignments();
};

#endif
