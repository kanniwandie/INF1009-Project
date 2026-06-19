#include "MenuController.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
using namespace std;

static string buildFilePath(const string& folder, const string& defaultName) {
    if (folder.empty()) return defaultName;
    if (folder.back() == '/' || folder.back() == '\\') return folder + defaultName;
    return folder + "/" + defaultName;
}

static bool openDataFile(ifstream& file, const string& defaultName, const string& label) {
    if (!file.is_open()) {
        cout << "[Notice] '" << defaultName << "' not found.\n";
        cout << "Enter file path for " << label << " file: ";
        string userPath;
        cin >> userPath;
        if (userPath.find(".txt") == string::npos) {
            if (!userPath.empty() && userPath.back() != '/' && userPath.back() != '\\') {
                userPath += "/";
            }
            userPath += defaultName;
        }
        file.open(userPath);
    }
    return file.is_open();
}

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

    string pPath = buildFilePath(folder, "passenger.txt");
    ifstream pFile(pPath);
    if (openDataFile(pFile, "passenger.txt", "passenger")) {
        string line, id, dest, time;
        while (getline(pFile, line)) {
            stringstream ss(line);
            if (getline(ss, id, ',') && getline(ss, dest, ',') && getline(ss, time, ',')) {
                string trimmedId = trim(id);
                if (pReg.findById(trimmedId) != nullptr) {
                    cout << "[Warning] Skipped duplicate Passenger ID in file: " << trimmedId << "\n";
                } else {
                    pReg.add(Passenger(trimmedId, trim(dest), trim(time)));
                }
            }
        }
        cout << "[RAM Storage] Successfully loaded passengers into memory.\n\n";
        pFile.close();
    } else {
        cout << "[Warning] Could not locate or open passenger data. Starting with empty storage.\n\n";
    }

    string sPath = buildFilePath(folder, "shuttle.txt");
    ifstream sFile(sPath);
    if (openDataFile(sFile, "shuttle.txt", "shuttle")) {
        string line, id, chargingPoint, time;
        while (getline(sFile, line)) {
            stringstream ss(line);
            if (getline(ss, id, ',') && getline(ss, chargingPoint, ',') && getline(ss, time, ',')) {
                string trimmedId = trim(id);
                if (sReg.findById(trimmedId) != nullptr) {
                    cout << "[Warning] Skipped duplicate Shuttle ID in file: " << trimmedId << "\n";
                } else {
                    sReg.add(ShuttleVehicle(trimmedId, trim(chargingPoint), trim(time)));
                }
            }
        }
        cout << "[RAM Storage] Successfully loaded shuttles into memory.\n\n";
        sFile.close();
    } else {
        cout << "[Warning] Could not locate or open shuttle data. Starting with empty storage.\n\n";
    }
}

void MenuController::editPassenger(PassengerList& pReg) {
    string id, newDest, newTime;
    cout << "Enter Passenger ID to edit: ";
    cin >> id;

    Passenger* p = pReg.findById(id);
    if (p) {
        cout << "Found " << p->getDescription() << "\n";
        cout << "Enter New Destination and New Time (separated by space): ";
        cin >> newDest >> newTime;
        p->setDestination(newDest);
        p->setScheduledTime(newTime);
        pReg.resetAssignments();
        cout << "[RAM Storage] Passenger updated successfully in-place.\n";
    } else {
        cout << "Passenger ID not found in RAM.\n";
    }
}

void MenuController::editShuttle(ShuttleList& sReg) {
    string id, newPoint, newTime;
    cout << "Enter Shuttle ID to edit: ";
    cin >> id;

    ShuttleVehicle* s = sReg.findById(id);
    if (s) {
        cout << "Found " << s->getDescription() << "\n";
        cout << "Enter New Charging Point and New Time (separated by space): ";
        cin >> newPoint >> newTime;
        s->setDestination(newPoint);
        s->setScheduledTime(newTime);
        sReg.resetAssignments();
        cout << "[RAM Storage] Shuttle updated successfully in-place.\n";
    } else {
        cout << "Shuttle ID not found in RAM.\n";
    }
}

void MenuController::handleDataManagementMenu(PassengerList& pReg, ShuttleList& sReg) {
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
        case 1:
            cout << "Enter ID, Destination, and Time (separated by spaces): ";
            cin >> id >> dest >> time;
            if (pReg.findById(id)) {
                cout << "Passenger ID already exists in RAM. Please choose a unique ID.\n";
                break;
            }
            pReg.add(Passenger(id, dest, time));
            pReg.resetAssignments();
            cout << "Passenger added to RAM.\n";
            break;
        case 2:
            cout << "Enter ID, Charging Point, and Time (separated by spaces): ";
            cin >> id >> dest >> time;
            if (sReg.findById(id)) {
                cout << "Shuttle ID already exists in RAM. Please choose a unique ID.\n";
                break;
            }
            sReg.add(ShuttleVehicle(id, dest, time));
            sReg.resetAssignments();
            cout << "Shuttle added to RAM.\n";
            break;
        case 3: editPassenger(pReg); break;
        case 4: editShuttle(sReg); break;
        case 5:
            cout << "Enter Passenger ID to remove: ";
            cin >> id;
            if (pReg.remove(id)) {
                pReg.resetAssignments();
                cout << "Removed from RAM.\n";
            } else {
                cout << "ID not found.\n";
            }
            break;
        case 6:
            cout << "Enter Shuttle ID to remove: ";
            cin >> id;
            if (sReg.remove(id)) {
                sReg.resetAssignments();
                cout << "Removed from RAM.\n";
            } else {
                cout << "ID not found.\n";
            }
            break;
        case 7: break;
        }
    }
}

void MenuController::displayAllData(const PassengerList& pReg, const ShuttleList& sReg) {
    cout << "\n=== ALL PASSENGERS ===\n";
    if (pReg.size() == 0) {
        cout << "No passengers loaded.\n";
    } else {
        for (size_t i = 0; i < pReg.size(); ++i) {
            cout << pReg[i].getDescription() << "\n";
        }
    }

    cout << "\n=== ALL SHUTTLES ===\n";
    if (sReg.size() == 0) {
        cout << "No shuttles loaded.\n";
    } else {
        for (size_t i = 0; i < sReg.size(); ++i) {
            cout << sReg[i].getDescription() << "\n";
        }
    }
}
