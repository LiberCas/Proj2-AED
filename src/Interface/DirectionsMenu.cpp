//
// Created by Acer on 22/01/2022.
//

#include "DirectionsMenu.h"

DirectionsMenu::DirectionsMenu(Controller& controller): Menu(controller) {
    mainOptions = {"Insert station ID", "Search for station by line", "Search for station by location", "Go Back"};
    currentInput = 'O';
}

bool DirectionsMenu::insertId() {
    string stopID = anyInputMenu("Please insert the ID, or type 'B' to go back");
    while(!checkStopId(stopID) && stopID!="B")
        stopID = anyInputMenu("Please insert the ID, or type 'B' to go back", "Invalid Input!");
    if(stopID == "B")
        return false;
    if(currentInput == 'O')
        origin = controller->findStop(stopID);
    else
        destination = controller->findStop(stopID);
    return true;
}

bool DirectionsMenu::searchByLine() {
    return true;
}

bool DirectionsMenu::searchByLoc() {
    return true;
}

bool DirectionsMenu::checkStopId(string id) {
    for(auto stop : controller->getStops())
        if(stop.getCode() == id)
            return true;
    return false;
}

void DirectionsMenu::nowGetting(char option) {
    currentInput = option;
}

void DirectionsMenu::showDirections() {
    string directions = controller->getDirections(origin, destination);
    singleInputScreen("Directions:\n"+ directions + "\nType 'B' to go back");
}


