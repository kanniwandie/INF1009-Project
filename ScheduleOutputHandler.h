/**
 * @file ScheduleOutputHandler.h
 * @brief Defines output abstractions for rendering schedules and registries in multiple formats.
 * @author Melia Kek Xin Hui
 */
#ifndef SCHEDULE_OUTPUT_HANDLER_H
#define SCHEDULE_OUTPUT_HANDLER_H

#include "Schedule.h"
#include "Registry.h"
#include "Entity.h"
#include <string>
#include <vector>
using namespace std;

/**
 * @brief Abstract output interface for rendering schedules and registry information.
 * @author Melia Kek Xin Hui
 */
class ScheduleOutputHandler {
public:
    virtual ~ScheduleOutputHandler() = default;
    virtual void writeSchedules(const vector<Schedule>& schedules, const string& strategyName) const = 0;
    virtual void writeUnassigned(const PassengerList& passengers, const ShuttleList& shuttles) const = 0;
    virtual void writeAllData(const PassengerList& passengers, const ShuttleList& shuttles) const = 0;

    /**
     * @brief Writes an overview of a mixed collection of entities through the shared Entity interface.
     * @param entities A collection of passenger and shuttle entities exposed as Entity pointers.
     */
    virtual void writeEntityOverview(const vector<const Entity*>& entities) const = 0;
};

/**
 * @brief Console-backed implementation of the schedule output abstraction.
 * @author Melia Kek Xin Hui
 */
class ConsolePrinter : public ScheduleOutputHandler {
public:
    void writeSchedules(const vector<Schedule>& schedules, const string& strategyName) const override;
    void writeUnassigned(const PassengerList& passengers, const ShuttleList& shuttles) const override;
    void writeAllData(const PassengerList& passengers, const ShuttleList& shuttles) const override;
    void writeEntityOverview(const vector<const Entity*>& entities) const override;
};

/**
 * @brief File-backed implementation that writes formatted output to text files.
 * @author Melia Kek Xin Hui
 */
class TextFileFormatter : public ScheduleOutputHandler {
private:
    string outputPath;

public:
    explicit TextFileFormatter(string path);
    bool saveSchedules(const vector<Schedule>& schedules, const string& strategyName) const;
    void writeSchedules(const vector<Schedule>& schedules, const string& strategyName) const override;
    void writeUnassigned(const PassengerList& passengers, const ShuttleList& shuttles) const override;
    void writeAllData(const PassengerList& passengers, const ShuttleList& shuttles) const override;
    void writeEntityOverview(const vector<const Entity*>& entities) const override;
};

#endif
