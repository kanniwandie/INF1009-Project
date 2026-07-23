#ifndef SCHEDULING_SERVICE_H
#define SCHEDULING_SERVICE_H

#include "ScheduleMatcher.h"
#include "ScheduleRepository.h"
#include <vector>
using namespace std;

class PassengerList;
class ShuttleList;

// Author: [Your Name]
// Purpose: Facade combining the matching engine (ScheduleMatcher) and schedule
// storage (ScheduleRepository) so callers depend on one small surface instead of
// two collaborating objects.
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
