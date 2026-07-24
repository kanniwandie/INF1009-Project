/**
 * @file IMatchingStrategy.h
 * @brief Declares the matching strategy interface and concrete strategy classes.
 * @author Yap Hui Xin
 */
#ifndef I_MATCHING_STRATEGY_H
#define I_MATCHING_STRATEGY_H

#include <string>
using namespace std;

class PassengerList;
class ShuttleList;
class ScheduleRepository;

/**
 * @brief Strategy interface used to evaluate passenger-shuttle compatibility.
 * @details Concrete strategies own the entire matching algorithm rather than a single
 * pairwise decision, because the minimum-dispatch and earliest-arrival policies are
 * fundamentally different global scheduling approaches. Keeping the algorithm behind
 * this interface allows the matcher to remain closed for modification when new dispatch
 * policies are introduced.
 * @author Yap Hui Xin
 */
class IMatchingStrategy {
public:
    virtual ~IMatchingStrategy() = default;

    /**
     * @brief Executes the matching algorithm using the supplied registries and repository.
     * @param passengers Passenger registry to evaluate.
     * @param shuttles Shuttle registry to evaluate.
     * @param repository Storage location for generated schedules.
     */
    virtual void match(PassengerList& passengers, ShuttleList& shuttles, ScheduleRepository& repository) const = 0;

    /**
     * @brief Returns the display name of the strategy.
     * @return Strategy name.
     */
    virtual string getName() const = 0;
};

/**
 * @brief Strategy that favours fewer shuttle dispatches by using larger-capacity shuttles first.
 * @details This policy packs as many passenger groups as possible onto each dispatched shuttle
 * before moving to the next one, helping to minimise the number of shuttles used.
 * @author Yap Hui Xin
 */
class MinimumDispatchStrategy : public IMatchingStrategy {
public:
    /**
     * @brief Executes the minimum-dispatch matching policy.
     * @param passengers Passenger registry to evaluate.
     * @param shuttles Shuttle registry to evaluate.
     * @param repository Storage location for generated schedules.
     */
    void match(PassengerList& passengers, ShuttleList& shuttles, ScheduleRepository& repository) const override;

    /**
     * @brief Returns the strategy name.
     * @return "Minimum Dispatch".
     */
    string getName() const override;
};

/**
 * @brief Strategy that chooses the shuttle which arrives earliest while still respecting the arrival window.
 * @details This policy prioritises passenger wait time over the total number of shuttles used.
 * @author Yap Hui Xin
 */
class EarliestArrivalStrategy : public IMatchingStrategy {
public:
    /**
     * @brief Executes the earliest-arrival matching policy.
     * @param passengers Passenger registry to evaluate.
     * @param shuttles Shuttle registry to evaluate.
     * @param repository Storage location for generated schedules.
     */
    void match(PassengerList& passengers, ShuttleList& shuttles, ScheduleRepository& repository) const override;

    /**
     * @brief Returns the strategy name.
     * @return "Earliest Arrival".
     */
    string getName() const override;
};

#endif
