// ****************************************************************************************************
// ****************************************** SYSTEM_CPP__ ********************************************
// ****************************************************************************************************

#include "System.h"
#include "OptionsMenu.h"
#include "DirectionsMenu.h"
#include <string>
#include <iostream>
using namespace std;

void System::clearScreen() {
    cout << string(50, '\n');
};


System::System() {
    controller = Controller();

    Menu startMenu = Menu(controller);
    OptionsMenu optionsMenu = OptionsMenu(controller);
    DirectionsMenu directionsMenu = DirectionsMenu(controller);

    while(true){
        int initOption = startMenu.printOptionsMenu({"Get directions", "Options"}, "Hello! What would you like to do?");
        if(initOption == 0){
            int dmOption;
            directionsMenu.nowGetting('O');
            while(true) {
                dmOption = directionsMenu.printOptionsMenu(directionsMenu.getMainOps(), "Origin:");
                if(dmOption == 0 && directionsMenu.insertId())
                    break;
                if(dmOption == 1 && directionsMenu.searchByLine())
                    break;
                if(dmOption == 2 && directionsMenu.searchByLoc())
                    break;
                if(dmOption == 3 && directionsMenu.insertCoordinates())
                    break;
                if(dmOption == 4)
                    break;
            }
            if (dmOption == 3) continue;
            directionsMenu.nowGetting('D');
            while(true) {
                dmOption = directionsMenu.printOptionsMenu(directionsMenu.getMainOps(), "Destination:");
                if(dmOption == 0 && directionsMenu.insertId())
                    break;
                if(dmOption == 1 && directionsMenu.searchByLine())
                    break;
                if(dmOption == 2 && directionsMenu.searchByLoc())
                    break;
                if(dmOption == 3)
                    break;
            }
            if (dmOption == 3) continue;
            directionsMenu.showDirections();
        }
        if (initOption == 1){
            optionsMenu.printOptionsMenu(optionsMenu.getMainOps());
        }
        if(initOption == 2) break;
    }
}