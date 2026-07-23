#include "SchedulingService.h"
#include "Registry.h"
#include <utility>
using namespace std;

void SchedulingService::setStrategy(unique_ptr<IMatchingStrategy> strategy) {
    matcher.setStrategy(std::move(strategy));
}

string SchedulingService::getStrategyName() const {
    return matcher.getStrategyName();
}

void SchedulingService::runMatchingAlgorithm(PassengerList& passengers, ShuttleList& shuttles) {
    repository.clear();
    passengers.resetAssignments();
    shuttles.resetAssignments();
    matcher.match(passengers, shuttles, repository);
}

const vector<Schedule>& SchedulingService::getSchedules() const {
    return repository.getSchedules();
}

void SchedulingService::clearSchedules() {
    repository.clear();
}
