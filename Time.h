/**
 * @file Time.h
 * @brief Declares the abstract time base class used by the scheduling domain.
 * @author Lee Jie Ying Jade
 */
#ifndef TIME_H
#define TIME_H

#include "TimeFormatter.h"
#include <memory>
#include <string>
using namespace std;

/**
 * @brief Abstract base class for time values with formatting and comparison support.
 * @details Concrete implementations provide domain-specific validation and comparison rules.
 * @author Lee Jie Ying Jade
 */
class Time {
protected:
    int hour;
    int minute;
    unique_ptr<TimeFormatter> formatter;

public:
    /**
     * @brief Constructs a time value with an hour, minute, and formatter.
     * @param hour Hour component.
     * @param minute Minute component.
     * @param formatter Optional formatter strategy for rendering.
     */
    Time(int hour = 0, int minute = 0, unique_ptr<TimeFormatter> formatter = nullptr);

    /**
     * @brief Destroys the time object.
     */
    virtual ~Time() = default;

    /**
     * @brief Checks whether the time value is valid for the scheduling domain.
     * @return True when the time is valid.
     */
    virtual bool isValid() const = 0;

    /**
     * @brief Converts the time to a formatted string.
     * @return Display string for the time value.
     */
    virtual string toString() const = 0;

    /**
     * @brief Compares this time object with another time object.
     * @param other Time value to compare against.
     * @return Negative, zero, or positive value depending on order.
     */
    virtual int compare(const Time& other) const = 0;

    /**
     * @brief Retrieves the hour component.
     * @return Hour value.
     */
    int getHour() const;

    /**
     * @brief Retrieves the minute component.
     * @return Minute value.
     */
    int getMinute() const;

    /**
     * @brief Updates the hour component.
     * @param newHour New hour value.
     */
    void setHour(int newHour);

    /**
     * @brief Updates the minute component.
     * @param newMinute New minute value.
     */
    void setMinute(int newMinute);

    /**
     * @brief Changes the formatter used to render the time.
     * @param newFormatter New time formatter strategy.
     */
    void setFormatter(unique_ptr<TimeFormatter> newFormatter);

    /**
     * @brief Compares this time with another time using the less-than operator.
     * @param other Time value to compare against.
     * @return True when this time is earlier than the other.
     */
    bool operator<(const Time& other) const;

    /**
     * @brief Compares this time with another time using the equality operator.
     * @param other Time value to compare against.
     * @return True when both times are equal.
     */
    bool operator==(const Time& other) const;
};

#endif
