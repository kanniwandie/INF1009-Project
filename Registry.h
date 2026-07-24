/**
 * @file Registry.h
 * @brief Provides generic and domain-specific registry containers for passengers and shuttles.
 * @author Lee Yu Huan
 */
#ifndef REGISTRY_H
#define REGISTRY_H

#include <vector>
#include <string>
using namespace std;

class Passenger;
class ShuttleVehicle;

/**
 * @brief Generic in-memory collection that stores domain objects keyed by ID.
 * @details The registry is intentionally domain-agnostic and only requires the stored
 * type to expose identifier access and assignment-state mutation. PassengerList and
 * ShuttleList compose this template instead of inheriting from it so the domain layer can
 * add specialised behaviour without leaking implementation details into the generic container.
 * @author Lee Yu Huan
 */
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

/**
 * @brief Domain-specific container for passenger objects.
 * @details PassengerList wraps a generic registry and exposes passenger-specific operations.
 * This composition keeps the domain concept explicit and prevents the passenger collection
 * from being treated as a bare generic registry.
 * @author Lee Yu Huan
 */
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

/**
 * @brief Domain-specific container for shuttle objects.
 * @details ShuttleList wraps the generic registry with shuttle-specific operations and keeps
 * the domain model explicit rather than exposing the storage implementation directly.
 * @author Lee Yu Huan
 */
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
