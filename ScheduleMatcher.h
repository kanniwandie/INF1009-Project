/**
 * @file ScheduleMatcher.h
 * @brief Executes the selected matching strategy against the passenger and shuttle registries.
 * @author Yap Hui Xin
 */
#ifndef SCHEDULE_MATCHER_H
#define SCHEDULE_MATCHER_H

#include "IMatchingStrategy.h"
#include <memory>
#include <string>
using namespace std;

class PassengerList;
class ShuttleList;
class ScheduleRepository;

/**
 * @brief Executes a pluggable matching strategy and writes the results into a repository.
 * @author Yap Hui Xin
 */
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
