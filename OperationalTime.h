/**
 * @file OperationalTime.h
 * @brief Declares the operational time object used for route and shuttle scheduling.
 * @author Lee Jie Ying Jade
 */
#ifndef OPERATIONAL_TIME_H
#define OPERATIONAL_TIME_H

#include "Time.h"

/**
 * @brief Concrete time object that validates times within the system's operating window.
 * @details The operational window begins at 06:00 and ends at 00:00, which is represented
 * using the same underlying time model with explicit validation rules.
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

    /**
     * @brief Constructs an operational time instance.
     * @param hour Hour component of the time.
     * @param minute Minute component of the time.
     * @param formatter Optional formatter strategy.
     */
    OperationalTime(int hour = START_HOUR, int minute = 0, unique_ptr<TimeFormatter> formatter = nullptr);

    /**
     * @brief Parses a raw time string into an operational time instance.
     * @param rawTime Input string in a supported time format.
     * @param formatter Optional formatter strategy.
     * @return Parsed operational time object, or null when parsing fails.
     */
    static unique_ptr<OperationalTime> parse(const string& rawTime, unique_ptr<TimeFormatter> formatter = nullptr);

    /**
     * @brief Checks whether the operational time falls inside the valid window.
     * @return True when the time is valid.
     */
    bool isValid() const override;

    /**
     * @brief Converts the operational time into a display string.
     * @return Formatted time string.
     */
    string toString() const override;

    /**
     * @brief Compares this operational time with another time object.
     * @param other Time value to compare against.
     * @return Comparison result for ordering.
     */
    int compare(const Time& other) const override;
};

#endif
