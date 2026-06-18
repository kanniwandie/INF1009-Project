#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include "Schedule.h"

class MenuController {
public:
    // Handles reading the folder path and parsing the files into RAM 
    static void loadDataFiles(PassengerList& pReg, ShuttleList& sReg);

    // Handles the CRUD interface operations
    static void handleDataManagementMenu(PassengerList& pReg, ShuttleList& sReg);
private:
    // Internal helpers
    static void editPassenger(PassengerList& pReg);
    static void editShuttle(ShuttleList& sReg);
};

#endif