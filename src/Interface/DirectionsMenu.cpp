//
// Created by Acer on 22/01/2022.
//

#include "DirectionsMenu.h"

DirectionsMenu::DirectionsMenu(Controller& controller): Menu(controller) {
    mainOptions = {"Insert station ID",
                   "Search for station by line",
                   "Search for station by location",
                   "Insert Coordinates",
                   "Go Back"};
    currentInput = 'O';
}

bool DirectionsMenu::insertId() {
    string stopID = anyInputMenu("Please insert the ID, or type 'B' to go back");
    while(!checkStopId(stopID) && stopID!="B")
        stopID = anyInputMenu("Please insert the ID, or type 'B' to go back", "Invalid Input!");
    if(stopID == "B")
        return false;
    if(currentInput == 'O')
        origin = stopID;
    else
        destination = stopID;
    return true;
}

bool DirectionsMenu::searchByLine() {
    string lineId = anyInputMenu("Please insert the line code, or type 'B' to go back");
    while(!checkLineId(lineId) && lineId!="B")
        lineId = anyInputMenu("Please insert the line code, or type 'B' to go back", "Invalid Input!");
    if(lineId == "B")
        return false;
    int orientation = printOptionsMenu({"Orientation 0", "Orientation 1", "Go Back"}, "Select Orientation");
    if(orientation == 2)
        return false;
    vector<string> stopsOptions;
    vector<int> searchLine;
    if(orientation)
        searchLine = controller->findLine(lineId).getL1();
    else
        searchLine = controller->findLine(lineId).getL0();
    for(auto stopIdx : searchLine)
        stopsOptions.push_back(controller->getGraph().getStop(stopIdx).getName());
    stopsOptions.push_back("Go Back");
    option = printOptionsMenu(stopsOptions, "Select Stop");
    if(option >= searchLine.size())
        return false;
    if(currentInput == 'O')
        origin = controller->getGraph().getStop(searchLine.at(option)).getCode();
    else
        destination = controller->getGraph().getStop(searchLine.at(option)).getCode();
    return true;
}

bool DirectionsMenu::searchByLoc() {
    return true;
}

void DirectionsMenu::nowGetting(char option) {
    currentInput = option;
}

void DirectionsMenu::showDirections() {
    string directions = controller->getDirections(origin, destination);
    singleInputScreen("Directions:\n"+ directions);
}

bool DirectionsMenu::insertCoordinates() {
    string latitudeStr = anyInputMenu("Please insert the x coordinate, or type 'B' to go back");
    while(!is_number(latitudeStr) && latitudeStr!="B")
        latitudeStr = anyInputMenu("Please insert the x coordinate, or type 'B' to go back", "Invalid Input!");
    if(latitudeStr == "B")
        return false;
    string longitudeStr = anyInputMenu("Please insert the y coordinate, or type 'B' to go back");
    while(!is_number(longitudeStr) && longitudeStr!="B")
        longitudeStr = anyInputMenu("Please insert the y coordinate, or type 'B' to go back", "Invalid Input!");
    if(longitudeStr == "B")
        return false;
    if(currentInput == 'O')
        origin = latitudeStr + "," + longitudeStr;
    else
        destination = latitudeStr + "," + longitudeStr;
    return true;
}

bool DirectionsMenu::checkStopId(string id) {
    for(auto stop : controller->getStops())
        if(stop.getCode() == id)
            return true;
    return false;
}

bool DirectionsMenu::checkLineId(string id) {
    for(auto line : controller->getLines())
        if(line.getCode() == id)
            return true;
    return false;
}


