/**
 * @file TimeFormatter.h
 * @brief Defines the formatter abstraction used by the time system.
 * @author Lee Jie Ying Jade
 */
#ifndef TIME_FORMATTER_H
#define TIME_FORMATTER_H

#include <string>
using namespace std;

/**
 * @brief Strategy interface for converting Time objects into display strings.
 * @author Lee Jie Ying Jade
 */
class TimeFormatter {
public:
    virtual ~TimeFormatter() = default;
    virtual string format(int hour, int minute) const = 0;
};

#endif
