#include "ScheduleMatcher.h"
#include <utility>
using namespace std;

ScheduleMatcher::ScheduleMatcher(unique_ptr<IMatchingStrategy> initialStrategy)
    : strategy(initialStrategy ? std::move(initialStrategy) : make_unique<MinimumDispatchStrategy>()) {
}

void ScheduleMatcher::setStrategy(unique_ptr<IMatchingStrategy> newStrategy) {
    if (newStrategy) {
        strategy = std::move(newStrategy);
    }
}

string ScheduleMatcher::getStrategyName() const {
    return strategy ? strategy->getName() : "None";
}

void ScheduleMatcher::match(PassengerList& passengers, ShuttleList& shuttles, ScheduleRepository& repository) const {
    if (strategy) {
        strategy->match(passengers, shuttles, repository);
    }
}
