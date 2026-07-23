#include "OperationalTime.h"
#include "AMPMTimeFormatter.h"
#include <algorithm>
#include <cctype>
#include <regex>

namespace {
string trim(const string& value) {
    size_t start = value.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = value.find_last_not_of(" \t\r\n");
    return value.substr(start, end - start + 1);
}

bool parseTimeValue(const string& raw, int& hour, int& minute) {
    const string value = trim(raw);

    static const regex timePattern(
        R"(^(\d{1,2}):(\d{2})\s*([aApP][mM])$)"
    );

    smatch match;

    if (!regex_match(value, match, timePattern)) {
        return false;
    }

    try {
        int hour12 = stoi(match[1].str());
        minute = stoi(match[2].str());

        char period = static_cast<char>(
            tolower(
                static_cast<unsigned char>(
                    match[3].str()[0]
                )
            )
        );

        if (minute < 0 || minute > 59) {
            return false;
        }

        if (hour12 == 0) {
            // 00:xxpm is not valid.
            if (period != 'a') {
                return false;
            }

            hour = 0;
            return true;
        }

        if (hour12 < 1 || hour12 > 12) {
            return false;
        }

        // Convert 12-hour time to 24-hour time.
        hour = hour12 % 12;

        if (period == 'p') {
            hour += 12;
        }

        return true;
    }
    catch (...) {
        return false;
    }
}

}
// Purpose: Implements the validated operational time domain object.
OperationalTime::OperationalTime(int hour, int minute, unique_ptr<TimeFormatter> formatter)
    : Time(hour, minute, std::move(formatter)) {}

unique_ptr<OperationalTime> OperationalTime::parse(const string& rawTime, unique_ptr<TimeFormatter> formatter) {
    int hour = 6;
    int minute = 0;
    if (!formatter) {
        formatter = make_unique<AMPMTimeFormatter>();
    }

    if (parseTimeValue(rawTime, hour, minute)) {
        return make_unique<OperationalTime>(hour, minute, std::move(formatter));
    }

    // Deliberately NOT falling back to a plausible-looking default like 6:00 AM
    // here: that would make garbage input (e.g. a malformed data file row)
    // silently masquerade as a legitimate, valid entity. hour = -1 guarantees
    // isValid() below correctly reports this object as invalid, so callers
    // (and the CRUD validation added to MenuController) can detect and reject
    // unparseable time strings instead of quietly accepting them.
    return make_unique<OperationalTime>(-1, -1, std::move(formatter));
}

bool OperationalTime::isValid() const {
    if (minute < 0 || minute > 59) {
        return false;
    }

    if (hour == 0 && minute == 0) {
        return true;
    }

    return hour >= 6 && hour <= 23;
}

string OperationalTime::toString() const {
    if (formatter) {
        return formatter->format(hour, minute);
    }
    return AMPMTimeFormatter().format(hour, minute);
}

int OperationalTime::compare(const Time& other) const {
    int lhs = hour * 60 + minute;
    int rhs = other.getHour() * 60 + other.getMinute();
    return lhs < rhs ? -1 : (lhs > rhs ? 1 : 0);
}
