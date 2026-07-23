#ifndef OPERATIONAL_TIME_H
#define OPERATIONAL_TIME_H

#include "Time.h"

// Purpose: Represents a validated operational shuttle time within the allowed service window.
class OperationalTime : public Time {
public:
    OperationalTime(int hour = 6, int minute = 0, unique_ptr<TimeFormatter> formatter = nullptr);

    static unique_ptr<OperationalTime> parse(const string& rawTime, unique_ptr<TimeFormatter> formatter = nullptr);

    bool isValid() const override;
    string toString() const override;
    int compare(const Time& other) const override;
};

#endif
