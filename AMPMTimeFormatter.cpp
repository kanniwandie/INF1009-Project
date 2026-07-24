/**
 * @file AMPMTimeFormatter.cpp
 * @brief Implements the 12-hour AM/PM formatter strategy.
 * @author Lee Jie Ying Jade
 */

#include "AMPMTimeFormatter.h"
#include <iomanip>
#include <sstream>
string AMPMTimeFormatter::format(int hour, int minute) const {
    string suffix = (hour >= 12) ? "PM" : "AM";
    int displayHour = hour % 12;
    if (displayHour == 0) {
        displayHour = 12;
    }

    stringstream stream;
    stream << displayHour << ":" << setw(2) << setfill('0') << minute << " " << suffix;
    return stream.str();
}
