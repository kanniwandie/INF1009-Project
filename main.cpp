/**
 * @file main.cpp
 * @brief Entry point for the driverless public transportation route-planner application.
 * @author Melia Kek Xin Hui
 */

#include "ScheduleManager.h"
#include "MenuController.h"
using namespace std;

int main() {
    ScheduleManager manager;
    MenuController controller(manager);
    controller.run();
    return 0;
}
