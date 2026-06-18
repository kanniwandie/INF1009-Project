#include "MenuController.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void MenuController::loadDataFiles(PassengerList& pReg, ShuttleList& sReg) {
    string defaultPassengerFile = "passenger.txt";
    string defaultShuttleFile = "shuttle.txt";

    ifstream pFile(defaultPassengerFile);
    if (!pFile.is_open()) {
        cout << "[Notice] 'passenger.txt' not found in the project folder.\n";
        cout << "Enter the specific file path or folder path for the passenger file: ";
        string userPath;
        cin >> userPath;

        if (userPath.find(".txt") == string::npos) {
            if (!userPath.empty() && userPath.back() != '/' && userPath.back() != '\\') {
                userPath += "/";
            }
            userPath += "passenger.txt";
        }
        pFile.open(userPath);
    }

    if (pFile.is_open()) {
        string line, id, dest, time;
        while (getline(pFile, line)) {
            stringstream ss(line);
            if (getline(ss, id, ',') && getline(ss, dest, ',') && getline(ss, time, ',')) {
                pReg.add(Passenger(id, dest, time));
            }
        }
        cout << "[RAM Storage] Successfully loaded passengers into memory.\n\n";
        pFile.close();
    } else {
        cout << "[Warning] Could not locate or open passenger data. Starting with empty storage.\n\n";
    }

    ifstream sFile(defaultShuttleFile);
    if (!sFile.is_open()) {
        cout << "[Notice] 'shuttle.txt' not found in the project folder.\n";
        cout << "Enter the specific file path or folder path for the shuttle file: ";
        string userPath;
        cin >> userPath;

        if (userPath.find(".txt") == string::npos) {
            if (!userPath.empty() && userPath.back() != '/' && userPath.back() != '\\') {
                userPath += "/";
            }
            userPath += "shuttle.txt";
        }
        sFile.open(userPath);
    }

    if (sFile.is_open()) {
        string line, id, chargingPoint, time;
        while (getline(sFile, line)) {
            stringstream ss(line);
            if (getline(ss, id, ',') && getline(ss, chargingPoint, ',') && getline(ss, time, ',')) {
                sReg.add(ShuttleVehicle(id, chargingPoint, time));
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
        cin >> choice;

        string id, dest, time;
        switch (choice) {
        case 1:
            cout << "Enter ID, Destination, and Time (separated by spaces): ";
            cin >> id >> dest >> time;
            pReg.add(Passenger(id, dest, time));
            cout << "Passenger added to RAM.\n";
            break;
        case 2:
            cout << "Enter ID, Charging Point, and Time (separated by spaces): ";
            cin >> id >> dest >> time;
            sReg.add(ShuttleVehicle(id, dest, time));
            cout << "Shuttle added to RAM.\n";
            break;
        case 3: editPassenger(pReg); break;
        case 4: editShuttle(sReg); break;
        case 5:
            cout << "Enter Passenger ID to remove: ";
            cin >> id;
            if (pReg.remove(id)) cout << "Removed from RAM.\n";
            else cout << "ID not found.\n";
            break;
        case 6:
            cout << "Enter Shuttle ID to remove: ";
            cin >> id;
            if (sReg.remove(id)) cout << "Removed from RAM.\n";
            else cout << "ID not found.\n";
            break;
        case 7: break;
        default: cout << "Invalid selection.\n";
        }
    }
}
