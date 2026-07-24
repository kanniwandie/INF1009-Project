/**
 * @file OperationalTime.h
 * @brief Declares the operational time object used for route and shuttle scheduling.
 * @author Lee Jie Ying Jade
 */
#ifndef OPERATIONAL_TIME_H
#define OPERATIONAL_TIME_H

#include "Time.h"

// Purpose: Represents a validated operational shuttle time within the allowed service window.
/**
 * @brief Concrete time object that validates times within the system's operating window.
 * @author Lee Jie Ying Jade
 */
class OperationalTime : public Time {
public:
    static constexpr int START_HOUR = 6;
    static constexpr int START_MINUTE = 0;
    static constexpr int MIDNIGHT_HOUR = 0;
    static constexpr int MIDNIGHT_MINUTE = 0;
    static constexpr int LAST_VALID_HOUR = 23;
    static constexpr int LAST_VALID_MINUTE = 59;

    OperationalTime(int hour = START_HOUR, int minute = 0, unique_ptr<TimeFormatter> formatter = nullptr);

    static unique_ptr<OperationalTime> parse(const string& rawTime, unique_ptr<TimeFormatter> formatter = nullptr);

    bool isValid() const override;
    string toString() const override;
    int compare(const Time& other) const override;
};

#endif
