#ifndef SCHEDULE_OUTPUT_HANDLER_H
#define SCHEDULE_OUTPUT_HANDLER_H

#include "Schedule.h"
#include <string>
#include <vector>
using namespace std;

// Author: [Your Name]
// Purpose: Output abstraction for rendering schedules and unassigned entries in multiple formats.
class ScheduleOutputHandler {
public:
    virtual ~ScheduleOutputHandler() = default;
    virtual void writeSchedules(const vector<Schedule>& schedules, const string& strategyName) const = 0;
    virtual void writeUnassigned(const PassengerList& passengers, const ShuttleList& shuttles) const = 0;
    virtual void writeAllData(const PassengerList& passengers, const ShuttleList& shuttles) const = 0;
};

class ConsolePrinter : public ScheduleOutputHandler {
public:
    void writeSchedules(const vector<Schedule>& schedules, const string& strategyName) const override;
    void writeUnassigned(const PassengerList& passengers, const ShuttleList& shuttles) const override;
    void writeAllData(const PassengerList& passengers, const ShuttleList& shuttles) const override;
};

class TextFileFormatter : public ScheduleOutputHandler {
private:
    string outputPath;

public:
    explicit TextFileFormatter(string path);
    void writeSchedules(const vector<Schedule>& schedules, const string& strategyName) const override;
    void writeUnassigned(const PassengerList& passengers, const ShuttleList& shuttles) const override;
    void writeAllData(const PassengerList& passengers, const ShuttleList& shuttles) const override;
};

#endif
