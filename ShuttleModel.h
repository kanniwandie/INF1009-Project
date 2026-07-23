#ifndef SHUTTLE_MODEL_H
#define SHUTTLE_MODEL_H

#include <memory>
#include <string>
using namespace std;

class ShuttleModel {
public:
    virtual ~ShuttleModel() = default;
    virtual int getMaxSeats() const = 0;
    virtual string getName() const = 0;
    // The exact token used in the Small/Family/Premium data file format and
    // expected back by ShuttleParser - distinct from getName(), which is a
    // human-readable label for console/report display (e.g. "Small Shuttle").
    virtual string getCode() const = 0;
    virtual unique_ptr<ShuttleModel> clone() const = 0;
};

class SmallShuttleModel : public ShuttleModel {
public:
    int getMaxSeats() const override;
    string getName() const override;
    string getCode() const override;
    unique_ptr<ShuttleModel> clone() const override;
};

class FamilyShuttleModel : public ShuttleModel {
public:
    int getMaxSeats() const override;
    string getName() const override;
    string getCode() const override;
    unique_ptr<ShuttleModel> clone() const override;
};

class PremiumShuttleModel : public ShuttleModel {
public:
    int getMaxSeats() const override;
    string getName() const override;
    string getCode() const override;
    unique_ptr<ShuttleModel> clone() const override;
};

#endif
