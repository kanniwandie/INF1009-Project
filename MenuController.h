/**
 * @file MenuController.h
 * @brief Handles the console-based menu flow and delegates work to the service layer.
 * @author Melia Kek Xin Hui
 */
#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include "ScheduleManager.h"
#include <string>
using namespace std;

// Purpose: UI/coordination layer only. Holds a reference to a ScheduleManager and
// translates console menu choices into calls on it; MenuController itself contains
// no file parsing, matching, or persistence logic - all of that was extracted into
// FileLoader/UserInputParser/SystemDataService/SchedulingService so this class can
// stay focused on presenting menus and reading input (SRP). It is instance-based
// (not a static-only utility class) so it can be constructed with the manager it
// coordinates, and mocked/replaced in tests if needed.
/**
 * @brief UI controller responsible for reading menu commands and dispatching them to the schedule manager.
 * @author Melia Kek Xin Hui
 */
class MenuController {
private:
    ScheduleManager& manager;
    static string normalizeModel(string model);
    void handleScheduleGeneration();
    void handleSaveArchive() const;
    void handleUnassignedDisplay() const;
    void handleSaveSystemData() const;

public:
    explicit MenuController(ScheduleManager& manager);

    void run();
    void loadDataFiles(const string& folder = "");
    void handleDataManagementMenu();
    void displayAllData() const;

    static int getMenuChoice(int min, int max);
    static string trim(const string& s);
};

#endif
