#ifndef ISO_TIME_FORMATTER_H
#define ISO_TIME_FORMATTER_H

#include "TimeFormatter.h"

// Author: [Your Name]
// Purpose: Formats time values using 24-hour ISO-style notation.
class ISOTimeFormatter : public TimeFormatter {
public:
    string format(int hour, int minute) const override;
};

#endif
