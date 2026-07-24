/**
 * @file MenuController.cpp
 * @brief Implements the console menu workflow and delegates business logic to the service layer.
 * @author Melia Kek Xin Hui
 */
#include "MenuController.h"
#include "OperationalTime.h"
#include "ScheduleOutputHandler.h"
#include "UserInputParser.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <sstream>

using namespace std;

namespace {
string readLineInput(const string& prompt) {
    cout << prompt;
    string line;
    getline(cin, line);
    return line;
}

vector<string> splitTokens(const string& line) {
    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

string normalizeModelName(const string& model) {
    string normalized = model;
    size_t start = normalized.find_first_not_of(" \t\r\n");
    if (start == string::npos) {
        return "";
    }
    size_t end = normalized.find_last_not_of(" \t\r\n");
    normalized = normalized.substr(start, end - start + 1);

    transform(normalized.begin(), normalized.end(), normalized.begin(), [](unsigned char ch) {
        return static_cast<char>(tolower(ch));
    });

    if (normalized == "small") {
        return "Small";
    }
    if (normalized == "family") {
        return "Family";
    }
    if (normalized == "premium") {
        return "Premium";
    }
    return "";
}

string joinTokens(const vector<string>& tokens, size_t start, size_t end) {
    string result;
    for (size_t i = start; i < end; ++i) {
        if (i > start) {
            result += ' ';
        }
        result += tokens[i];
    }
    return result;
}

bool parsePassengerInputLine(const string& inputLine, string& id, string& destination, string& time, int& groupSize, string& errorMessage) {
    vector<string> tokens = splitTokens(inputLine);
    if (tokens.size() < 4) {
        errorMessage = "Error: Please enter at least 4 values: ID, Destination, Time, Group Size.";
        return false;
    }

    id = tokens[0];
    destination = joinTokens(tokens, 1, tokens.size() - 2);
    time = tokens[tokens.size() - 2];

    try {
        groupSize = stoi(tokens.back());
    } catch (...) {
        errorMessage = "Error: Group Size must be a whole number. Entry rejected.";
        return false;
    }

    auto parsedTime = OperationalTime::parse(time);
    if (!parsedTime || !parsedTime->isValid()) {
        errorMessage = "Error: Passenger entry rejected because the requested time falls outside the operational window (06:00am to 00:00am). It was not added to RAM.";
        return false;
    }

    return true;
}

bool parseShuttleInputLine(const string& inputLine, string& id, string& destination, string& time, string& model, string& errorMessage) {
    vector<string> tokens = splitTokens(inputLine);
    if (tokens.size() < 4) {
        errorMessage = "Error: Please enter at least 4 values: ID, Destination, Time, Model.";
        return false;
    }

    id = tokens[0];
    destination = joinTokens(tokens, 1, tokens.size() - 2);
    time = tokens[tokens.size() - 2];
    model = normalizeModelName(tokens.back());

    auto parsedTime = OperationalTime::parse(time);
    if (!parsedTime || !parsedTime->isValid()) {
        errorMessage = "Error: Shuttle entry rejected because the requested time falls outside the operational window (06:00am to 00:00am). It was not added to RAM.";
        return false;
    }

    return true;
}
}

MenuController::MenuController(ScheduleManager& manager) : manager(manager) {
}

string MenuController::trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

string MenuController::normalizeModel(string model) {
    model = trim(model);

    transform(model.begin(), model.end(), model.begin(), [](unsigned char ch) { 
            return static_cast<char>(tolower(ch));
        }
    );

    if (model == "small") {
        return "Small";
    }

    if (model == "family") {
        return "Family";
    }

    if (model == "premium") {
        return "Premium";
    }

    return "";
}

int MenuController::getMenuChoice(int min, int max) {
    while (true) {
        string line;
        getline(cin, line);
        if (cin.eof()) {
            cout << "\nInput stream ended unexpectedly. Closing application.\n";
            exit(0);
        }

        try {
            int choice = stoi(line);
            if (choice >= min && choice <= max) {
                return choice;
            }
        } catch (...) {
        }

        cout << "Invalid input. Enter a number between " << min << " and " << max << ": ";
    }
}

void MenuController::loadDataFiles(const string& folder) {
    LoadResult result = manager.loadAllSystemData(folder);

    if (result.allLoaded()) {
        cout << "[RAM Storage] Successfully loaded data into memory.\n\n";
    } else if (result.anyLoaded()) {
        cout << "[Warning] Partially loaded data: "
             << (result.passengerLoaded ? "passenger.txt OK, shuttle.txt could not be loaded"
                                         : "shuttle.txt OK, passenger.txt could not be loaded")
             << ". The data that did load is available; the rest is empty.\n\n";
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

    string filename = readLineInput("Enter filename to archive the '" + manager.getStrategyName()
                                     + "' route plan (e.g., minimum_dispatch_run.txt): ");

    TextFileFormatter formatter(filename);

    if (formatter.saveSchedules(
            manager.getSchedules(),
            manager.getStrategyName()
        )) {
        cout << "Route plan saved to "
            << filename << "\n";
    }
    else {
        cout << "Error: Could not save route plan to "
            << filename << "\n";
    }
}

void MenuController::handleUnassignedDisplay() const {
    ConsolePrinter printer;
    printer.writeUnassigned(manager.getPassengerRegistry(), manager.getShuttleRegistry());
}

void MenuController::handleSaveSystemData() const {
    /*
     * Application Requirement 10: save passenger/shuttle data to NEW files -
     * never overwrite the originals, and only ever on explicit user request.
     */
    string passengerPath = readLineInput("Enter a NEW filename for passenger data (e.g. passenger_updated.txt): ");
    string shuttlePath = readLineInput("Enter a NEW filename for shuttle data (e.g. shuttle_updated.txt): ");

    if (passengerPath == shuttlePath) {
        cout << "Error: Passenger and shuttle files must use "
            << "different filenames.\n";
        return;
    }

    auto fileExists = [](const string& path) {
        ifstream input(path.c_str());
        return input.good();
    };

    if (fileExists(passengerPath) || fileExists(shuttlePath)) {
        cout << "Error: One or both filenames already exist. "
            << "Enter new filenames.\n";
        return;
    }

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
            string inputLine = readLineInput("Enter ID, Destination, Time and Group Size (1-15) (Eg. P01 School 7:20am 5 -> separated by space): ");
            int groupSize = 1;
            string errorMessage;
            if (!parsePassengerInputLine(inputLine, id, dest, time, groupSize, errorMessage)) {
                cout << errorMessage << "\n";
                break;
            }
            if (pReg.containsId(id)) {
                cout << "Error: Passenger entry rejected because the passenger ID '" << id << "' already exists. It was not added to RAM.\n";
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
            string inputLine = readLineInput("Enter ID, Charging Point, Time, and Model (Small/Family/Premium) (Eg. S01 School 7:15am Small -> separated by spaces): ");
            string errorMessage;
            if (!parseShuttleInputLine(inputLine, id, dest, time, model, errorMessage)) {
                cout << errorMessage << "\n";
                break;
            }
            if (sReg.containsId(id)) {
                cout << "Error: Shuttle entry rejected because the shuttle ID '" << id << "' already exists. It was not added to RAM.\n";
                break;
            }
            if (model.empty()) {
                cout << "Error: Model must be Small, Family, or Premium. " << "Entry rejected.\n";
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
            editId = readLineInput("Enter Passenger ID to edit: ");
            Passenger* passenger = pReg.findById(editId);
            if (!passenger) {
                cout << "Error: Passenger ID '" << editId << "' does not exist.\n";
            } else {
                cout << "Found " << passenger->getDescription() << "\n";
                string inputLine = readLineInput("Enter New Destination, New Time, and New Group Size (1-15) (Home 8:00pm 4 -> separated by space): ");
                vector<string> tokens = splitTokens(inputLine);
                if (tokens.size() < 3) {
                    cout << "Error: Please enter at least 3 values: Destination, Time, Group Size.\n";
                    break;
                }

                newDest = joinTokens(tokens, 0, tokens.size() - 2);
                newTime = tokens[tokens.size() - 2];
                try {
                    newGroupSize = stoi(tokens.back());
                } catch (...) {
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

                auto parsedPassengerEditTime = OperationalTime::parse(newTime);
                if (!parsedPassengerEditTime || !parsedPassengerEditTime->isValid()) {
                    cout << "Error: Passenger update cancelled because the requested time falls outside the operational window (06:00am to 00:00am). The existing entry was kept unchanged.\n";
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
            editId = readLineInput("Enter Shuttle ID to edit: ");
            ShuttleVehicle* shuttle = sReg.findById(editId);
            if (!shuttle) {
                cout << "Error: Shuttle ID '" << editId << "' does not exist.\n";
            } else {
                cout << "Found " << shuttle->getDescription() << "\n";
                string inputLine = readLineInput("Enter New Charging Point, New Time, and New Model (Small/Family/Premium) (Home 7:00pm Family -> separated by space): ");
                vector<string> tokens = splitTokens(inputLine);
                if (tokens.size() < 3) {
                    cout << "Error: Please enter at least 3 values: Destination, Time, Model.\n";
                    break;
                }

                newPoint = joinTokens(tokens, 0, tokens.size() - 2);
                newTime = tokens[tokens.size() - 2];
                newModel = normalizeModel(tokens.back());

                if (newModel.empty()) {
                    cout << "Error: Model must be Small, Family, or Premium. " << "Edit cancelled.\n";
                    break;
                }
                if (trim(newPoint).empty()) {
                    cout << "Error: Charging Point cannot be empty. Edit cancelled.\n";
                    break;
                }

                auto parsedShuttleEditTime = OperationalTime::parse(newTime);
                if (!parsedShuttleEditTime || !parsedShuttleEditTime->isValid()) {
                    cout << "Error: Shuttle update cancelled because the requested time falls outside the operational window (06:00am to 00:00am). The existing entry was kept unchanged.\n";
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
            id = readLineInput("Enter Passenger ID to remove: ");
            if (pReg.remove(id)) {
                pReg.resetAssignments();
                cout << "Removed from RAM.\n";
            } else {
                cout << "Error: Passenger ID '" << id << "' does not exist.\n";
            }
            break;
        case 6:
            id = readLineInput("Enter Shuttle ID to remove: ");
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
