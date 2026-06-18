#ifndef REGISTRY_H
#define REGISTRY_H

#include <vector>
#include <string>
#include <algorithm>
using namespace std;

template <typename T>
class Registry {
protected:
    vector<T> items;

public:
    Registry() = default;
    virtual ~Registry() = default;

    void add(const T& item) {
        items.push_back(item);
    }

    bool remove(const string& id) {
        auto it = remove_if(items.begin(), items.end(), [&id](const T& item) {
            return item.getID() == id;
        });
        if (it != items.end()) {
            items.erase(it, items.end());
            return true;
        }
        return false;
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

#endif
