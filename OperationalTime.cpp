#include "OperationalTime.h"
#include "AMPMTimeFormatter.h"
#include <algorithm>
#include <cctype>

namespace {
string trim(const string& value) {
    size_t start = value.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = value.find_last_not_of(" \t\r\n");
    return value.substr(start, end - start + 1);
}

bool parseTimeValue(const string& raw, int& hour, int& minute) {
    string value = trim(raw);
    if (value.empty()) return false;

    transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
        return static_cast<char>(tolower(ch));
    });

    bool isAm = true;
    size_t suffixPos = value.find("am");
    if (suffixPos != string::npos) {
        value.erase(suffixPos, 2);
    } else {
        suffixPos = value.find("pm");
        if (suffixPos != string::npos) {
            isAm = false;
            value.erase(suffixPos, 2);
        }
    }

    value.erase(remove(value.begin(), value.end(), ' '), value.end());

    size_t separatorPos = string::npos;
    if ((separatorPos = value.find(':')) == string::npos) {
        separatorPos = value.find('.');
    }

    if (separatorPos == string::npos) return false;

    try {
        hour = stoi(value.substr(0, separatorPos));
        minute = stoi(value.substr(separatorPos + 1));
    } catch (...) {
        return false;
    }

    if (!isAm && hour < 12) hour += 12;
    if (isAm && hour == 12) hour = 0;
    return true;
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

    if (hour < 6 || hour > 24) {
        return false;
    }

    if (hour == 24 && minute != 0) {
        return false;
    }

    return true;
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
