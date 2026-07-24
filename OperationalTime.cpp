/**
 * @file OperationalTime.cpp
 * @brief Implements the operational time object used for route and shuttle scheduling.
 * @author Lee Jie Ying Jade
 */

#include "OperationalTime.h"
#include "AMPMTimeFormatter.h"
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <sstream>

namespace {
constexpr int OPERATIONAL_START_HOUR = 6;
constexpr int OPERATIONAL_START_MINUTE = 0;
constexpr int OPERATIONAL_END_HOUR = 23;
constexpr int OPERATIONAL_END_MINUTE = 59;
constexpr int MIDNIGHT_HOUR = 0;
constexpr int MIDNIGHT_MINUTE = 0;

string trim(const string& value) {
    size_t first = value.find_first_not_of(" \t\r\n");
    if (first == string::npos) {
        return "";
    }

    size_t last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}
}

OperationalTime::OperationalTime(int hour, int minute, unique_ptr<TimeFormatter> formatter)
    : Time(hour, minute, std::move(formatter)) {
    if (this->formatter == nullptr) {
        this->formatter = make_unique<AMPMTimeFormatter>();
    }
}

unique_ptr<OperationalTime> OperationalTime::parse(const string& rawTime, unique_ptr<TimeFormatter> formatter) {
    auto result = make_unique<OperationalTime>(-1, 0, std::move(formatter));
    string text = trim(rawTime);
    if (text.empty()) {
        return result;
    }

    string lower = text;
    transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char ch) {
        return static_cast<char>(tolower(ch));
    });

    bool isPM = false;
    if (lower.size() >= 2 && (lower.substr(lower.size() - 2) == "pm" || lower.substr(lower.size() - 2) == "am")) {
        isPM = lower.substr(lower.size() - 2) == "pm";
        lower = lower.substr(0, lower.size() - 2);
    }

    lower = trim(lower);
    if (lower.empty()) {
        return result;
    }

    size_t separator = lower.find(':');
    if (separator == string::npos) {
        separator = lower.find('.');
    }

    int hour = 0;
    int minute = 0;

    try {
        if (separator == string::npos) {
            hour = stoi(lower);
        } else {
            string hourPart = trim(lower.substr(0, separator));
            string minutePart = trim(lower.substr(separator + 1));
            if (hourPart.empty() || minutePart.empty()) {
                return result;
            }
            hour = stoi(hourPart);
            minute = stoi(minutePart);
        }
    } catch (const invalid_argument&) {
        return result;
    } catch (const out_of_range&) {
        return result;
    }

    if (hour < 0 || hour > 12 || minute < 0 || minute > 59) {
        return result;
    }

    if (hour == 12) {
        hour = isPM ? 12 : 0;
    } else if (isPM) {
        hour += 12;
    }

    if (hour == 24) {
        hour = 0;
    }

    result->setHour(hour);
    result->setMinute(minute);
    return result;
}

bool OperationalTime::isValid() const {
    const bool isMidnight = (hour == MIDNIGHT_HOUR && minute == MIDNIGHT_MINUTE);
    const bool isWithinServiceWindow = hour >= OPERATIONAL_START_HOUR && hour <= OPERATIONAL_END_HOUR
        && minute >= OPERATIONAL_START_MINUTE && minute <= OPERATIONAL_END_MINUTE;
    return isMidnight || isWithinServiceWindow;
}

string OperationalTime::toString() const {
    if (!isValid()) {
        return "Invalid Time";
    }

    if (formatter == nullptr) {
        return "Invalid Time";
    }

    return formatter->format(hour, minute);
}

int OperationalTime::compare(const Time& other) const {
    const int thisTotal = hour * 60 + minute;
    const int otherTotal = other.getHour() * 60 + other.getMinute();
    if (thisTotal < otherTotal) {
        return -1;
    }
    if (thisTotal > otherTotal) {
        return 1;
    }
    return 0;
}
