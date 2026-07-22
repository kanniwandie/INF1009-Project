#include "MenuController.h"
#include "FileLoader.h"
#include "ScheduleOutputHandler.h"
#include "SystemDataService.h"
#include "UserInputParser.h"
#include <iostream>
#include <limits>
using namespace std;

string MenuController::trim(const string& s) {
    size_t start = s.find_first_not_of(" \t");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t");
    return s.substr(start, end - start + 1);
}

int MenuController::getMenuChoice(int min, int max) {
    int choice;
    while (!(cin >> choice) || choice < min || choice > max) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a number between " << min << " and " << max << ": ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

void MenuController::loadDataFiles(PassengerList& pReg, ShuttleList& sReg, const string& folder) {
    pReg.clear();
    sReg.clear();

    if (SystemDataService::loadInitialData(pReg, sReg, folder)) {
        cout << "[RAM Storage] Successfully loaded data into memory.\n\n";
    } else {
        cout << "[Warning] Could not load data files. Starting with empty storage.\n\n";
    }
}

void MenuController::handleDataManagementMenu(PassengerList& pReg, ShuttleList& sReg) {
    SystemDataService dataService;
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
            cout << "Enter ID, Destination, Time, and Group Size (separated by spaces): ";
            cin >> id >> dest >> time >> groupSize;
            if (pReg.containsId(id)) {
                cout << "Error: Passenger ID '" << id << "' already exists.\n";
                break;
            }
            UserInputParser inputParser;
            string rawEntry = id + "," + dest + "," + time + "," + to_string(groupSize);
            if (!inputParser.parsePassengerInput(rawEntry, pReg, sReg)) {
                cout << "Passenger entry could not be parsed.\n";
                break;
            }
            pReg.resetAssignments();
            cout << "Passenger added to RAM.\n";
            break;
        }
        case 2: {
            string model = "Small";
            cout << "Enter ID, Charging Point, Time, and Model (separated by spaces): ";
            cin >> id >> dest >> time >> model;
            if (sReg.containsId(id)) {
                cout << "Error: Shuttle ID '" << id << "' already exists.\n";
                break;
            }
            UserInputParser inputParser;
            string rawEntry = id + "," + dest + "," + time + "," + model;
            if (!inputParser.parseShuttleInput(rawEntry, pReg, sReg)) {
                cout << "Shuttle entry could not be parsed.\n";
                break;
            }
            sReg.resetAssignments();
            cout << "Shuttle added to RAM.\n";
            break;
        }
        case 3: {
            string id, newDest, newTime;
            int newGroupSize = 1;
            cout << "Enter Passenger ID to edit: ";
            cin >> id;
            Passenger* passenger = pReg.findById(id);
            if (!passenger) {
                cout << "Error: Passenger ID '" << id << "' does not exist.\n";
            } else {
                cout << "Found " << passenger->getDescription() << "\n";
                cout << "Enter New Destination, New Time, and New Group Size (separated by space): ";
                cin >> newDest >> newTime >> newGroupSize;
                if (dataService.editPassenger(pReg, id, newDest, newTime, newGroupSize)) {
                    cout << "[RAM Storage] Passenger updated successfully in-place.\n";
                } else {
                    cout << "Passenger update failed.\n";
                }
            }
            break;
        }
        case 4: {
            string id, newPoint, newTime, newModel;
            cout << "Enter Shuttle ID to edit: ";
            cin >> id;
            ShuttleVehicle* shuttle = sReg.findById(id);
            if (!shuttle) {
                cout << "Error: Shuttle ID '" << id << "' does not exist.\n";
            } else {
                cout << "Found " << shuttle->getDescription() << "\n";
                cout << "Enter New Charging Point, New Time, and New Model (separated by space): ";
                cin >> newPoint >> newTime >> newModel;
                if (dataService.editShuttle(sReg, id, newPoint, newTime, newModel)) {
                    cout << "[RAM Storage] Shuttle updated successfully in-place.\n";
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

void MenuController::displayAllData(const PassengerList& pReg, const ShuttleList& sReg) {
    ConsolePrinter printer;
    printer.writeAllData(pReg, sReg);
}
