// ****************************************************************************************************
// ****************************************** CONTROLLER_CPP__ ****************************************
// ****************************************************************************************************

#include "Controller.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>


Controller::Controller() {
    //------------------------------------------------------------------Stops
    ifstream stopsFile;
    stopsFile.open("../src/dataset/stops.csv");
    if (stopsFile.fail()) {
        cout << "This file doesn't exist!\n";
    } else {
        /*string line;
        stopsFile >> line;
        while (!stopsFile.eof()) {
            Stop stop;
            stopsFile >> stop;
            this->stopDB.push_back(stop);
        }*/
    }
    stopsFile.close();
    //------------------------------------------------------------------Lines

    ifstream linesFile;
    linesFile.open("../src/dataset/lines.csv");
    if (linesFile.fail()) {
        cout << "This file doesn't exist!\n";
    } else {
        string l;
        stopsFile >> l;
        while (!linesFile.eof()) {
            Line line;
            linesFile >> line;
            if (line.getCode()=="300"||line.getCode()=="301"||line.getCode()=="302"||line.getCode()=="303" ){
                line.setL0(readEachLineFile0(line.getCode()));
            }
            else {
                line.setL0(readEachLineFile0(line.getCode()));
                line.setL1(readEachLineFile1(line.getCode()));
            }
            this->linesDB.push_back(line);

        }
    }
    linesFile.close();
}

vector<Stop> Controller::readEachLineFile0(string code) {
    vector<Stop> res;
    ifstream linesFile;
    string filename = "../src/dataset/line_" + code + "_0.csv";
    linesFile.open(filename);
    if (linesFile.fail()) {
        cout << "This file doesn't exist!";
    } else {
        int i;
        linesFile >> i;
        for(int n=0;n<i;n++){
            string code;
            linesFile >> code;
            bool stop = existsStop(code);
            if(stop){
                Stop s = findStop(code);
                res.push_back(s);
            }
        }
    }
    return res;

}

vector<Stop> Controller::readEachLineFile1(string code) {
    vector<Stop> res;
    ifstream linesFile;
    string filename = "../src/dataset/line_" + code + "_1.csv";
    linesFile.open(filename);
    if (linesFile.fail()) {
        cout << "This file doesn't exist!";
    } else {
        int i;
        linesFile >> i;
        for(int n=0;n<i;n++){
            string code;
            linesFile >> code;
            bool stop = existsStop(code);
            if(stop){
                Stop s = findStop(code);
                res.push_back(s);
            }
        }
    }
    return res;
}
Controller::~Controller(){
    stopDB.clear();
    linesDB.clear();
}

vector<Line> Controller::getLines() {
    return linesDB;
}

vector<Stop> Controller::getStops() {
    return stopDB;
}


Stop& Controller::findStop(string code) {
    for(int i=0; i<stopDB.size(); i++)
        if(stopDB[i].getCode() == code)
            return stopDB[i];
    Stop* nill = new Stop();
    return *nill;
}

Line& Controller::findLine(string code) {
    for(auto& line :linesDB){
        if(line.getCode()==code)
            return line;
    }
    Line* nill=NULL;
    return *nill;
}



bool Controller::existsStop(string code) {
    for(auto& stop :stopDB){
        if(stop.getCode()==code)
            return true;
    }
    return false;
}



void Controller::addStop(string code, string name, string zone, float latitude, float longitude) {
    Stop stop = Stop(code,name,zone,latitude,longitude);
    stopDB.push_back(stop);
}


bool Controller::removeStop(string code) {
    for(auto stop : stopDB);
    vector<Stop>::iterator it;
    for(it = stopDB.begin(); it<stopDB.end(); it++)
        if(it->getCode()==code){
            stopDB.erase(it);
            return true;
        }
    return false;
}



Stop Controller::getClosestStop() {

    return Stop();
}

string Controller::getDirections(Stop origin, Stop destination) {
    return "Por aí";
}

void Controller::writeFiles() {

}






/*
void Controller::writeFiles() {
    //------------------------------------------------------------------Airports
    ofstream airportFile;
    airportFile.open("airports.txt");
    for(int i = 0; i<airportDB.size(); i++){
        airportFile << airportDB[i];
        if(i!=airportDB.size()-1)
            airportFile<<"\n";
    }
    airportFile.close();
    //------------------------------------------------------------------Flights
    ofstream flightsFile;
    flightsFile.open("flights.txt");
    for(int i = 0; i<flightDB.size(); i++){
        flightsFile << flightDB[i];
        if(i!=flightDB.size()-1)
            flightsFile<<"\n";
    }
    flightsFile.close();
    //------------------------------------------------------------------Passengers
    ofstream passengersFile;
    passengersFile.open("passengers.txt");
    for(int i = 0; i<passengerDB.size(); i++){
        passengersFile << passengerDB[i];
        if(i!=passengerDB.size()-1)
            passengersFile<<"\n";
    }
    passengersFile.close();
    //------------------------------------------------------------------Planes
    ofstream planesFile;
    planesFile.open("planes.txt");
    for(int i = 0; i<planeDB.size(); i++){
        planesFile << planeDB[i];
        if(i!=planeDB.size()-1)
            planesFile<<"\n";
    }
    planesFile.close();
}

*/
