#include "Schedule.h"
#include "SchedulePrinter.h"
#include "ScheduleStorage.h"
#include "MenuController.h"
#include <iostream>
#include <limits>
using namespace std;

int main() {
    ScheduleList systemScheduler;
    PassengerList& pReg = systemScheduler.getPassengerRegistry();
    ShuttleList& sReg = systemScheduler.getShuttleRegistry();

    cout << "=== Welcome Route-Planner Application ===\n";

    string folder;
    cout << "Enter folder path (or press Enter for current directory): ";
    getline(cin, folder);
    MenuController::loadDataFiles(pReg, sReg, folder);

    int menuChoice = 0;
    while (menuChoice != 7) {
        cout << "\n================ MAIN MENU ================\n"
             << "1. Compute and Display Match Schedules\n"
             << "2. Display Unassigned Entities\n"
             << "3. Save Computed Schedules to Archive\n"
             << "4. Manage RAM Local Parameters (Add/Edit/Delete)\n"
             << "5. Display All Data\n"
             << "6. Reload Data Files\n"
             << "7. Exit Application\n"
             << "Selection: ";
        menuChoice = MenuController::getMenuChoice(1, 7);

        switch (menuChoice) {
        case 1:
            systemScheduler.generateSchedules();
            SchedulePrinter::printActiveSchedules(systemScheduler.getActiveSchedules());
            break;
        case 2:
            SchedulePrinter::printUnassignedEntities(pReg, sReg);
            break;
        case 3: {
            string filename;
            cout << "Enter filename to archive output (e.g., final_run.txt): ";
            cin >> filename;
            ScheduleStorage::saveSchedules(filename, systemScheduler.getActiveSchedules());
            break;
        }
        case 4:
            systemScheduler.clearSchedules();
            MenuController::handleDataManagementMenu(pReg, sReg);
            break;
        case 5:
            MenuController::displayAllData(pReg, sReg);
            break;
        case 6: {
            cout << "Enter folder path (or press Enter for current directory): ";
            getline(cin, folder);
            systemScheduler.clearSchedules();
            MenuController::loadDataFiles(pReg, sReg, folder);
            break;
        }
        case 7:
            cout << "Closing scheduling system. Memory cleared.\n";
            break;
        }
    }
    return 0;
}
