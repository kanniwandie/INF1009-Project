#ifndef SCHEDULE_MATCHER_H
#define SCHEDULE_MATCHER_H

#include "IMatchingStrategy.h"
#include <memory>
#include <string>
using namespace std;

class PassengerList;
class ShuttleList;
class ScheduleRepository;

// Author: [Your Name]
// Purpose: Runs a pluggable IMatchingStrategy (Strategy Pattern) against the
// passenger/shuttle registries and records results into a ScheduleRepository.
// Extracted from the former ScheduleList god-class so "how matching is executed"
// is separate from "what data is being matched" and "where results are stored".
class ScheduleMatcher {
private:
    unique_ptr<IMatchingStrategy> strategy;

public:
    explicit ScheduleMatcher(unique_ptr<IMatchingStrategy> initialStrategy = nullptr);

    void setStrategy(unique_ptr<IMatchingStrategy> newStrategy);
    string getStrategyName() const;
    void match(PassengerList& passengers, ShuttleList& shuttles, ScheduleRepository& repository) const;
};

#endif
