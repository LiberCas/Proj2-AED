// ****************************************************************************************************
// ****************************************** SYSTEM_CPP__ ********************************************
// ****************************************************************************************************

#include "System.h"
#include "OptionsMenu.h"
#include "DirectionsMenu.h"
#include <string>
#include <iostream>
#include <regex>

using namespace std;

void System::clearScreen() {
    cout << string(50, '\n');
};


System::System() {
    controller = Controller();

    if(!controller.readUserData()){
        Menu firstOpeningMenu = Menu(controller);
        string input = firstOpeningMenu.anyInputMenu("Welcome new user! Please insert a username:");
        controller.setUsername(input);
        input = firstOpeningMenu.anyInputMenu("From 1 to 10, how much do you like to walk?");
        while (!firstOpeningMenu.checkIntInput(input,1,10))
            input = firstOpeningMenu.anyInputMenu("From 1 to 10, how much do you like to walk?", "Invalid Input!");
        controller.setWalkingFac(stoi(input));
        input = firstOpeningMenu.anyInputMenu("What is the maximum distance you would like to walk, in meters?");
        while (!firstOpeningMenu.checkIntInput(input))
            input = firstOpeningMenu.anyInputMenu("What is the maximum distance you would like to walk, in meters?", "Invalid Input!");
        controller.setMaxWalkDist(stoi(input));
        clearScreen();
    }

    controller.addEdgesInWalkingDistance();
    Menu startMenu = Menu(controller);
    OptionsMenu optionsMenu = OptionsMenu(controller);
    DirectionsMenu directionsMenu = DirectionsMenu(controller);

    while(true){
        int initOption = startMenu.printOptionsMenu({"Get directions", "Options"}, "Hello "+ controller.getUsername() +"! What would you like to do?");
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
                if(dmOption == 3 && directionsMenu.insertCoordinates())
                    break;
                if(dmOption == 4)
                    break;
            }
            if (dmOption == 3) continue;
            directionsMenu.showDirections();
        }
        if (initOption == 1){
            int omOption = optionsMenu.printOptionsMenu(optionsMenu.getMainOps());
            while (omOption != 3){
                if(omOption == 0)
                    optionsMenu.setWalkingFactor();
                if(omOption == 1)
                    optionsMenu.setMaxWalkingDistance();
                if(omOption == 2)
                    optionsMenu.setUsername();
                omOption = optionsMenu.printOptionsMenu(optionsMenu.getMainOps());
            }
        }
        if(initOption == 2) break;

    }
}
/*
string System::fixString(string str) {
    size_t index = 0;
    while (true) {
        index = str.find("├", index);
        if (index == std::string::npos) break;
        cout<<"hey\n";
        str.replace(index, 1, "E");

        index += 1;
    }
    str = regex_replace(str, regex("├"), "E");
    return str;
}*/
