/**
 * @file ISOTimeFormatter.h
 * @brief Formats times in 24-hour ISO-style notation.
 * @author Lee Jie Ying Jade
 */
#ifndef ISO_TIME_FORMATTER_H
#define ISO_TIME_FORMATTER_H

#include "TimeFormatter.h"

// Purpose: Formats time values using 24-hour ISO-style notation.
/**
 * @brief Formats a time value in 24-hour ISO style.
 * @author Lee Jie Ying Jade
 */
class ISOTimeFormatter : public TimeFormatter {
public:
    string format(int hour, int minute) const override;
};

#endif
