/**
 * @file SchedulingService.h
 * @brief Combines matching and schedule storage into one application-facing service.
 * @author Yap Hui Xin
 */
#ifndef SCHEDULING_SERVICE_H
#define SCHEDULING_SERVICE_H

#include "ScheduleMatcher.h"
#include "ScheduleRepository.h"
#include <vector>
using namespace std;

class PassengerList;
class ShuttleList;

/**
 * @brief Facade that runs a matching strategy and stores the resulting schedules.
 * @author Yap Hui Xin
 */
class SchedulingService {
private:
    ScheduleMatcher matcher;
    ScheduleRepository repository;

public:
    void setStrategy(unique_ptr<IMatchingStrategy> strategy);
    string getStrategyName() const;
    void runMatchingAlgorithm(PassengerList& passengers, ShuttleList& shuttles);
    const vector<Schedule>& getSchedules() const;
    void clearSchedules();
};

#endif
