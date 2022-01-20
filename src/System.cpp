// ****************************************************************************************************
// ****************************************** SYSTEM_CPP__ ********************************************
// ****************************************************************************************************

#include "System.h"
#include "StartMenu.h"
#include <string>
#include <iostream>
using namespace std;

void System::clearScreen() {
    cout << string(50, '\n');
};


System::System() {
    controller = Controller();

    StartMenu startMenu = StartMenu(controller);
    while(true){
        int initOption = startMenu.printOptionsMenu(startMenu.getMainOps(), "Which one are you?");
        if(initOption == 0){}

    }
}