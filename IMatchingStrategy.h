#ifndef I_MATCHING_STRATEGY_H
#define I_MATCHING_STRATEGY_H

#include <string>
#include <vector>
using namespace std;

class Passenger;
class ShuttleVehicle;

// Author: [Your Name]
// Purpose: Strategy interface for evaluating compatible passenger-shuttle matches.
class IMatchingStrategy {
public:
    virtual ~IMatchingStrategy() = default;
    virtual bool shouldMatch(const Passenger& passenger, const ShuttleVehicle& shuttle) const = 0;
    virtual string getName() const = 0;
};

class MinimumDispatchStrategy : public IMatchingStrategy {
public:
    bool shouldMatch(const Passenger& passenger, const ShuttleVehicle& shuttle) const override;
    string getName() const override;
};

class EarliestArrivalStrategy : public IMatchingStrategy {
public:
    bool shouldMatch(const Passenger& passenger, const ShuttleVehicle& shuttle) const override;
    string getName() const override;
};

#endif
