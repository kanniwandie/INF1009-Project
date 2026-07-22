#ifndef TIME_H
#define TIME_H

#include "TimeFormatter.h"
#include <memory>
#include <string>
using namespace std;

// Author: [Your Name]
// Purpose: Abstract base class for time domain objects.
class Time {
protected:
    int hour;
    int minute;
    unique_ptr<TimeFormatter> formatter;

public:
    Time(int hour = 0, int minute = 0, unique_ptr<TimeFormatter> formatter = nullptr);
    virtual ~Time() = default;

    virtual bool isValid() const = 0;
    virtual string toString() const = 0;
    virtual int compare(const Time& other) const = 0;

    int getHour() const;
    int getMinute() const;
    void setHour(int newHour);
    void setMinute(int newMinute);
    void setFormatter(unique_ptr<TimeFormatter> newFormatter);

    bool operator<(const Time& other) const;
    bool operator==(const Time& other) const;
};

#endif
