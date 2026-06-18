#ifndef REGISTRY_H
#define REGISTRY_H
// For template class, both the definition and implementation must remain in the header file so the compiler can instantiate it properly
#include <vector>
#include <string>
#include <algorithm>

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

    vector<T>& getModifiableItems() {
        return items;
    }

    void resetAssignments() {
        for (auto& item : items) {
            item.setAssignedStatus(false);
        }
    }
};

#endif