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

/**
 * @brief UI controller responsible for reading menu commands and dispatching them to the schedule manager.
 * @details This class keeps the console-facing workflow separate from data loading, matching,
 * and persistence logic. It delegates the heavy work to the service layer so the controller
 * remains focused on menu presentation and user interaction.
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
