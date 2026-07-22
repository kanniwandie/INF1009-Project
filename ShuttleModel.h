#ifndef SHUTTLE_MODEL_H
#define SHUTTLE_MODEL_H

#include <memory>
#include <string>
using namespace std;

// Author: [Your Name]
class ShuttleModel {
public:
    virtual ~ShuttleModel() = default;
    virtual int getMaxSeats() const = 0;
    virtual string getName() const = 0;
    virtual unique_ptr<ShuttleModel> clone() const = 0;
};

class SmallShuttleModel : public ShuttleModel {
public:
    int getMaxSeats() const override;
    string getName() const override;
    unique_ptr<ShuttleModel> clone() const override;
};

class FamilyShuttleModel : public ShuttleModel {
public:
    int getMaxSeats() const override;
    string getName() const override;
    unique_ptr<ShuttleModel> clone() const override;
};

class PremiumShuttleModel : public ShuttleModel {
public:
    int getMaxSeats() const override;
    string getName() const override;
    unique_ptr<ShuttleModel> clone() const override;
};

#endif
