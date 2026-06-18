#include "Schedule.h"
#include "SchedulePrinter.h"
#include "ScheduleStorage.h"
#include "MenuController.h"
#include <iostream>

using namespace std;

int main() {
    ScheduleList systemScheduler;
    PassengerList& pReg = systemScheduler.getPassengerRegistry();
    ShuttleList& sReg = systemScheduler.getShuttleRegistry();

    cout << "=== Welcome Route-Planner Application ===\n";
    MenuController::loadDataFiles(pReg, sReg); //

    int menuChoice = 0;
    while (menuChoice != 5) {
        cout << "\n================ MAIN MENU ================\n"
            << "1. Compute and Display Match Schedules\n"
            << "2. Display Unassigned Entities\n"
            << "3. Save Computed Schedules to Archive\n"
            << "4. Manage RAM Local Parameters (Add/Edit/Delete)\n"
            << "5. Exit Application\n"
            << "Selection: ";
        cin >> menuChoice;

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
            if (ScheduleStorage::saveSchedules(filename, systemScheduler.getActiveSchedules())) {
                cout << "Archive saved successfully.\n";
            }
            else {
                cerr << "Error creating archive file.\n";
            }
            break;
        }
        case 4:
            MenuController::handleDataManagementMenu(pReg, sReg); // Extracted Out!
            break;
        case 5:
            cout << "Closing scheduling system. Memory cleared.\n";
            break;
        default:
            cout << "Invalid entry. Try again.\n";
        }
    }
    return 0;
}