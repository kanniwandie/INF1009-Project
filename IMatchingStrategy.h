#ifndef I_MATCHING_STRATEGY_H
#define I_MATCHING_STRATEGY_H

#include <string>
using namespace std;

class PassengerList;
class ShuttleList;
class ScheduleRepository;

// Author: [Your Name]
// Purpose: Strategy Pattern interface for computing the full set of passenger-shuttle
// schedules. Concrete strategies own the entire matching algorithm (not just a single
// pairwise rule) because "minimum dispatch" and "earliest arrival" are genuinely
// different global policies: one prioritizes filling the fewest shuttles, the other
// prioritizes each passenger's fastest match. Keeping the whole algorithm behind this
// interface lets ScheduleMatcher stay closed for modification (OCP) when new dispatch
// policies are added later.
class IMatchingStrategy {
public:
    virtual ~IMatchingStrategy() = default;
    virtual void match(PassengerList& passengers, ShuttleList& shuttles, ScheduleRepository& repository) const = 0;
    virtual string getName() const = 0;
};

// Fills the highest-capacity eligible shuttle first, packing as many passenger groups
// as possible onto each dispatched shuttle before moving to the next one. This keeps
// the total number of shuttles dispatched to a minimum (Application Requirement 6).
class MinimumDispatchStrategy : public IMatchingStrategy {
public:
    void match(PassengerList& passengers, ShuttleList& shuttles, ScheduleRepository& repository) const override;
    string getName() const override;
};

// For each passenger (in registry order), dispatches the eligible shuttle with the
// earliest arrival time, prioritizing passenger wait time over the number of shuttles
// used (Application Requirement 7).
class EarliestArrivalStrategy : public IMatchingStrategy {
public:
    void match(PassengerList& passengers, ShuttleList& shuttles, ScheduleRepository& repository) const override;
    string getName() const override;
};

#endif
