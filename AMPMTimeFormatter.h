#ifndef AMPM_TIME_FORMATTER_H
#define AMPM_TIME_FORMATTER_H

#include "TimeFormatter.h"

// Purpose: Formats time values using 12-hour AM/PM notation.
class AMPMTimeFormatter : public TimeFormatter {
public:
    string format(int hour, int minute) const override;
};

#endif
