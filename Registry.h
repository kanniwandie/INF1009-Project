#ifndef REGISTRY_H
#define REGISTRY_H

#include <vector>
#include <string>
#include <algorithm>
#include <utility>
using namespace std;

class Passenger;
class ShuttleVehicle;

template <typename T>
class Registry {
protected:
    vector<T> items;

public:
    Registry() = default;
    virtual ~Registry() = default;

    Registry(const Registry& other) = default;
    Registry& operator=(const Registry& other) = default;

    void add(const T& item) {
        if (containsId(item.getID())) {
            return;
        }
        items.push_back(item);
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

class ShuttleList : public Registry<ShuttleVehicle> {};
class PassengerList : public Registry<Passenger> {};

#endif
