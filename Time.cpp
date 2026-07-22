#include "Time.h"

// Author: [Your Name]
// Purpose: Implements the common base behavior for all time-domain classes.
Time::Time(int hour, int minute, unique_ptr<TimeFormatter> formatter)
    : hour(hour), minute(minute), formatter(std::move(formatter)) {}

int Time::getHour() const { return hour; }
int Time::getMinute() const { return minute; }
void Time::setHour(int newHour) { hour = newHour; }
void Time::setMinute(int newMinute) { minute = newMinute; }
void Time::setFormatter(unique_ptr<TimeFormatter> newFormatter) {
    formatter = std::move(newFormatter);
}

bool Time::operator<(const Time& other) const {
    return compare(other) < 0;
}

bool Time::operator==(const Time& other) const {
    return compare(other) == 0;
}
