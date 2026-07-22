#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include "Schedule.h"
#include <string>
using namespace std;

class MenuController {
public:
    static void loadDataFiles(PassengerList& pReg, ShuttleList& sReg, const string& folder = "");
    static void handleDataManagementMenu(PassengerList& pReg, ShuttleList& sReg);
    static void displayAllData(const PassengerList& pReg, const ShuttleList& sReg);
    static int getMenuChoice(int min, int max);
    static string trim(const string& s);
};

#endif
