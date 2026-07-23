#include "MenuController.h"
#include "ScheduleOutputHandler.h"
#include "UserInputParser.h"
#include <iostream>
#include <limits>
#include <cstdlib>
using namespace std;

MenuController::MenuController(ScheduleManager& manager) : manager(manager) {
}

string MenuController::trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

int MenuController::getMenuChoice(int min, int max) {
    int choice;
    while (!(cin >> choice) || choice < min || choice > max) {
        if (cin.eof()) {
            cout << "\nInput stream ended unexpectedly. Closing application.\n";
            exit(0);
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a number between " << min << " and " << max << ": ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

void MenuController::loadDataFiles(const string& folder) {
    if (manager.loadAllSystemData(folder)) {
        cout << "[RAM Storage] Successfully loaded data into memory.\n\n";
    } else {
        cout << "[Warning] Could not load data files. Starting with empty storage.\n\n";
    }
}

void MenuController::handleScheduleGeneration() {
    cout << "\n--- Select Matching Algorithm ---\n"
         << "1. Minimum Shuttle Dispatch (fewest shuttles used)\n"
         << "2. Earliest Passenger Arrival (fastest match per passenger)\n"
         << "Selection: ";
    int choice = getMenuChoice(1, 2);

    if (choice == 1) {
        manager.setMatchingStrategy(make_unique<MinimumDispatchStrategy>());
    } else {
        manager.setMatchingStrategy(make_unique<EarliestArrivalStrategy>());
    }

    manager.runMatchingAlgorithm();

    ConsolePrinter printer;
    printer.writeSchedules(manager.getSchedules(), manager.getStrategyName());
}

void MenuController::handleSaveArchive() const {
    if (manager.getSchedules().empty()) {
        cout << "No computed schedule to save. Generate a schedule first (Option 1).\n";
        return;
    }

    string filename;
    cout << "Enter filename to archive the '" << manager.getStrategyName()
         << "' route plan (e.g., minimum_dispatch_run.txt): ";
    cin >> filename;

    TextFileFormatter formatter(filename);
    formatter.writeSchedules(manager.getSchedules(), manager.getStrategyName());
    cout << "Route plan saved to " << filename << "\n";
}

void MenuController::handleUnassignedDisplay() const {
    ConsolePrinter printer;
    printer.writeUnassigned(manager.getPassengerRegistry(), manager.getShuttleRegistry());
}

void MenuController::handleSaveSystemData() const {
    // Application Requirement 10: save passenger/shuttle data to NEW files -
    // never overwrite the originals, and only ever on explicit user request.
    string passengerPath, shuttlePath;
    cout << "Enter a NEW filename for passenger data (e.g. passenger_updated.txt): ";
    cin >> passengerPath;
    cout << "Enter a NEW filename for shuttle data (e.g. shuttle_updated.txt): ";
    cin >> shuttlePath;

    bool passengerSaved = manager.savePassengerData(passengerPath);
    bool shuttleSaved = manager.saveShuttleData(shuttlePath);

    if (passengerSaved) {
        cout << "Passenger data saved to " << passengerPath << "\n";
    } else {
        cout << "Error: Could not write passenger data to " << passengerPath << "\n";
    }
    if (shuttleSaved) {
        cout << "Shuttle data saved to " << shuttlePath << "\n";
    } else {
        cout << "Error: Could not write shuttle data to " << shuttlePath << "\n";
    }
}

void MenuController::displayAllData() const {
    ConsolePrinter printer;
    printer.writeAllData(manager.getPassengerRegistry(), manager.getShuttleRegistry());
    printer.writeEntityOverview(manager.getAllEntities());
}

void MenuController::handleDataManagementMenu() {
    PassengerList& pReg = manager.getPassengerRegistry();
    ShuttleList& sReg = manager.getShuttleRegistry();

    int choice = 0;
    while (choice != 7) {
        cout << "\n--- RAM Local Data Storage Management ---\n"
             << "1. Add Passenger\n"
             << "2. Add Shuttle\n"
             << "3. Edit Passenger Parameters\n"
             << "4. Edit Shuttle Parameters\n"
             << "5. Delete Passenger\n"
             << "6. Delete Shuttle\n"
             << "7. Back to Main Menu\n"
             << "Selection: ";
        choice = getMenuChoice(1, 7);

        string id, dest, time;
        switch (choice) {
        case 1: {
            int groupSize = 1;
            cout << "Enter ID, Destination, Time, and Group Size (1-15) (separated by spaces): ";
            cin >> id >> dest >> time >> groupSize;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Error: Group Size must be a whole number. Entry rejected.\n";
                break;
            }
            if (pReg.containsId(id)) {
                cout << "Error: Passenger ID '" << id << "' already exists.\n";
                break;
            }
            if (groupSize < 1 || groupSize > 15) {
                cout << "Error: Group Size must be between 1 and 15 (got " << groupSize << "). Entry rejected.\n";
                break;
            }
            if (trim(dest).empty()) {
                cout << "Error: Destination cannot be empty. Entry rejected.\n";
                break;
            }
            UserInputParser inputParser;
            string rawEntry = id + "," + dest + "," + time + "," + to_string(groupSize);
            if (!inputParser.parsePassengerInput(rawEntry, pReg, sReg)) {
                cout << "Passenger entry could not be parsed.\n";
                break;
            }
            Passenger* added = pReg.findById(id);
            if (!added || !added->isValid()) {
                if (added) pReg.remove(id);
                cout << "Error: Passenger entry failed validation (check the ID/time format) and was discarded.\n";
                break;
            }
            pReg.resetAssignments();
            cout << "Passenger added to RAM.\n";
            break;
        }
        case 2: {
            string model = "Small";
            cout << "Enter ID, Charging Point, Time, and Model (Small/Family/Premium) (separated by spaces): ";
            cin >> id >> dest >> time >> model;
            if (sReg.containsId(id)) {
                cout << "Error: Shuttle ID '" << id << "' already exists.\n";
                break;
            }
            if (model != "Small" && model != "Family" && model != "Premium") {
                cout << "Error: Model must be exactly one of Small, Family, or Premium (got '" << model << "'). Entry rejected.\n";
                break;
            }
            if (trim(dest).empty()) {
                cout << "Error: Charging Point cannot be empty. Entry rejected.\n";
                break;
            }
            UserInputParser inputParser;
            string rawEntry = id + "," + dest + "," + time + "," + model;
            if (!inputParser.parseShuttleInput(rawEntry, pReg, sReg)) {
                cout << "Shuttle entry could not be parsed.\n";
                break;
            }
            ShuttleVehicle* added = sReg.findById(id);
            if (!added || !added->isValid()) {
                if (added) sReg.remove(id);
                cout << "Error: Shuttle entry failed validation (must operate between 6:00 AM and 12:00 AM) and was discarded.\n";
                break;
            }
            sReg.resetAssignments();
            cout << "Shuttle added to RAM.\n";
            break;
        }
        case 3: {
            string editId, newDest, newTime;
            int newGroupSize = 1;
            cout << "Enter Passenger ID to edit: ";
            cin >> editId;
            Passenger* passenger = pReg.findById(editId);
            if (!passenger) {
                cout << "Error: Passenger ID '" << editId << "' does not exist.\n";
            } else {
                cout << "Found " << passenger->getDescription() << "\n";
                cout << "Enter New Destination, New Time, and New Group Size (1-15) (separated by space): ";
                cin >> newDest >> newTime >> newGroupSize;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Error: Group Size must be a whole number. Edit cancelled.\n";
                    break;
                }
                if (newGroupSize < 1 || newGroupSize > 15) {
                    cout << "Error: Group Size must be between 1 and 15 (got " << newGroupSize << "). Edit cancelled.\n";
                    break;
                }
                if (trim(newDest).empty()) {
                    cout << "Error: Destination cannot be empty. Edit cancelled.\n";
                    break;
                }

                Passenger before = *passenger;
                if (manager.editPassenger(editId, newDest, newTime, newGroupSize)) {
                    Passenger* updated = pReg.findById(editId);
                    if (updated && !updated->isValid()) {
                        *updated = before;
                        cout << "Error: Edit produced an invalid passenger (check the time format) and was rolled back.\n";
                    } else {
                        cout << "[RAM Storage] Passenger updated successfully in-place.\n";
                    }
                } else {
                    cout << "Passenger update failed.\n";
                }
            }
            break;
        }
        case 4: {
            string editId, newPoint, newTime, newModel;
            cout << "Enter Shuttle ID to edit: ";
            cin >> editId;
            ShuttleVehicle* shuttle = sReg.findById(editId);
            if (!shuttle) {
                cout << "Error: Shuttle ID '" << editId << "' does not exist.\n";
            } else {
                cout << "Found " << shuttle->getDescription() << "\n";
                cout << "Enter New Charging Point, New Time, and New Model (Small/Family/Premium) (separated by space): ";
                cin >> newPoint >> newTime >> newModel;

                if (newModel != "Small" && newModel != "Family" && newModel != "Premium") {
                    cout << "Error: Model must be exactly one of Small, Family, or Premium (got '" << newModel << "'). Edit cancelled.\n";
                    break;
                }
                if (trim(newPoint).empty()) {
                    cout << "Error: Charging Point cannot be empty. Edit cancelled.\n";
                    break;
                }

                ShuttleVehicle before = *shuttle;
                if (manager.editShuttle(editId, newPoint, newTime, newModel)) {
                    ShuttleVehicle* updated = sReg.findById(editId);
                    if (updated && !updated->isValid()) {
                        *updated = before;
                        cout << "Error: Edit produced an invalid shuttle (must operate 6:00 AM - 12:00 AM) and was rolled back.\n";
                    } else {
                        cout << "[RAM Storage] Shuttle updated successfully in-place.\n";
                    }
                } else {
                    cout << "Shuttle update failed.\n";
                }
            }
            break;
        }
        case 5:
            cout << "Enter Passenger ID to remove: ";
            cin >> id;
            if (pReg.remove(id)) {
                pReg.resetAssignments();
                cout << "Removed from RAM.\n";
            } else {
                cout << "Error: Passenger ID '" << id << "' does not exist.\n";
            }
            break;
        case 6:
            cout << "Enter Shuttle ID to remove: ";
            cin >> id;
            if (sReg.remove(id)) {
                sReg.resetAssignments();
                cout << "Removed from RAM.\n";
            } else {
                cout << "Error: Shuttle ID '" << id << "' does not exist.\n";
            }
            break;
        case 7: break;
        }
    }
}

void MenuController::run() {
    cout << "=== Welcome Route-Planner Application ===\n";

    string folder;
    cout << "Enter folder path (or press Enter for current directory): ";
    getline(cin, folder);
    loadDataFiles(folder);

    int menuChoice = 0;
    while (menuChoice != 8) {
        cout << "\n================ MAIN MENU ================\n"
             << "1. Compute and Display Match Schedules\n"
             << "2. Display Unassigned Entities\n"
             << "3. Save Computed Schedules to Archive\n"
             << "4. Manage RAM Local Parameters (Add/Edit/Delete)\n"
             << "5. Display All Data\n"
             << "6. Reload Data Files\n"
             << "7. Save Passenger/Shuttle Data to New Files\n"
             << "8. Exit Application\n"
             << "Selection: ";
        menuChoice = getMenuChoice(1, 8);

        switch (menuChoice) {
        case 1:
            handleScheduleGeneration();
            break;
        case 2:
            handleUnassignedDisplay();
            break;
        case 3:
            handleSaveArchive();
            break;
        case 4:
            manager.clearSchedules();
            handleDataManagementMenu();
            break;
        case 5:
            displayAllData();
            break;
        case 6: {
            cout << "Enter folder path (or press Enter for current directory): ";
            getline(cin, folder);
            manager.clearSchedules();
            loadDataFiles(folder);
            break;
        }
        case 7:
            handleSaveSystemData();
            break;
        case 8:
            cout << "Closing scheduling system. Memory cleared.\n";
            break;
        }
    }
}
