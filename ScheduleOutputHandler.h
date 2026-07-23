#ifndef SCHEDULE_OUTPUT_HANDLER_H
#define SCHEDULE_OUTPUT_HANDLER_H

#include "Schedule.h"
#include "Registry.h"
#include "Entity.h"
#include <string>
#include <vector>
using namespace std;

// Purpose: Output abstraction for rendering schedules and unassigned entries in multiple formats.
class ScheduleOutputHandler {
public:
    virtual ~ScheduleOutputHandler() = default;
    virtual void writeSchedules(const vector<Schedule>& schedules, const string& strategyName) const = 0;
    virtual void writeUnassigned(const PassengerList& passengers, const ShuttleList& shuttles) const = 0;
    virtual void writeAllData(const PassengerList& passengers, const ShuttleList& shuttles) const = 0;

    // Genuinely polymorphic: entities is a mixed collection of Passengers and
    // ShuttleVehicles, exposed only through the shared Entity interface. This
    // method (and its overrides) never knows or checks which concrete type any
    // given element is - getType()/getDescription()/isValid() dispatch correctly
    // at runtime for each element via virtual calls.
    virtual void writeEntityOverview(const vector<const Entity*>& entities) const = 0;
};

class ConsolePrinter : public ScheduleOutputHandler {
public:
    void writeSchedules(const vector<Schedule>& schedules, const string& strategyName) const override;
    void writeUnassigned(const PassengerList& passengers, const ShuttleList& shuttles) const override;
    void writeAllData(const PassengerList& passengers, const ShuttleList& shuttles) const override;
    void writeEntityOverview(const vector<const Entity*>& entities) const override;
};

class TextFileFormatter : public ScheduleOutputHandler {
private:
    string outputPath;

public:
    explicit TextFileFormatter(string path);
    void writeSchedules(const vector<Schedule>& schedules, const string& strategyName) const override;
    void writeUnassigned(const PassengerList& passengers, const ShuttleList& shuttles) const override;
    void writeAllData(const PassengerList& passengers, const ShuttleList& shuttles) const override;
    void writeEntityOverview(const vector<const Entity*>& entities) const override;
};

#endif
