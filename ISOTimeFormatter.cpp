#include "ISOTimeFormatter.h"
#include <iomanip>
#include <sstream>

// Purpose: Implements the 24-hour ISO formatter strategy.
string ISOTimeFormatter::format(int hour, int minute) const {
    stringstream stream;
    stream << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute;
    return stream.str();
}
