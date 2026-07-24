/**
 * @file ISOTimeFormatter.cpp
 * @brief Implements the 24-hour ISO formatter strategy.
 * @author Lee Jie Ying Jade
 */

#include "ISOTimeFormatter.h"
#include <iomanip>
#include <sstream>
string ISOTimeFormatter::format(int hour, int minute) const {
    stringstream stream;
    stream << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute;
    return stream.str();
}
