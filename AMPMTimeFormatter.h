/**
 * @file AMPMTimeFormatter.h
 * @brief Formats times in 12-hour AM/PM notation.
 * @author Lee Jie Ying Jade
 */
#ifndef AMPM_TIME_FORMATTER_H
#define AMPM_TIME_FORMATTER_H

#include "TimeFormatter.h"

/**
 * @brief Formats a time value using a 12-hour AM/PM convention.
 * @author Lee Jie Ying Jade
 */
class AMPMTimeFormatter : public TimeFormatter {
public:
    string format(int hour, int minute) const override;
};

#endif
