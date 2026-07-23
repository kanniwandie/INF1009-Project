#include "ScheduleManager.h"
#include "MenuController.h"
using namespace std;

int main() {
    ScheduleManager manager;
    MenuController controller(manager);
    controller.run();
    return 0;
}
