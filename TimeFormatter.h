#ifndef TIME_FORMATTER_H
#define TIME_FORMATTER_H

#include <string>
using namespace std;

// Purpose: Strategy interface for formatting clock values.
class TimeFormatter {
public:
    virtual ~TimeFormatter() = default;
    virtual string format(int hour, int minute) const = 0;
};

#endif
