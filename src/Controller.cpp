// ****************************************************************************************************
// ****************************************** CONTROLLER_CPP__ ****************************************
// ****************************************************************************************************

#include "Controller.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>


Controller::Controller() {
    //------------------------------------------------------------------Stops
    ifstream stopsFile;
    stopsFile.open("../src/dataset/stops.csv");
    if (stopsFile.fail()) {
        cout << "This file doesn't exist!\n";
    } else {
        string line;
        stopsFile >> line;
        while (!stopsFile.eof()) {
            Stop stop;
            stopsFile >> stop;
            this->stopDB.push_back(stop);
        }
    }
    stopsFile.close();
    this->graph = Graph(stopDB.size());
    for (int i=0;i<stopDB.size();i++){
        graph.addStop(stopDB[i]);
    }
    //------------------------------------------------------------------Lines
    ///TODO Erro aqui
    ifstream linesFile;
    linesFile.open("../src/dataset/lines.csv");
    if (linesFile.fail()) {
        cout << "This file doesn't exist!\n";
    } else {
        string l;
        linesFile >> l;
        linesFile.ignore();
        while (!linesFile.eof()) {
            Line line;
            linesFile >> line;
            if (line.getCode()=="") break;
            else if (line.getCode()=="300"||line.getCode()=="301"||line.getCode()=="302"||line.getCode()=="303" ){
                line.setL0(readEachLineFile0(line.getCode()));
                for (int i = 0; i<line.getL0().size()-1;i++){
                    line.getL0()[i].addEdge(Edge(line.getL0()[i+1],haversine(line.getL0()[i].getLatitude(),line.getL0()[i].getLongitude(),line.getL0()[i+1].getLatitude(),line.getL0()[i+1].getLongitude()),line.getCode()));
                }
            }
            else {
                line.setL0(readEachLineFile0(line.getCode()));
                for (int i = 0; i<line.getL0().size()-1;i++){
                    line.getL0()[i].addEdge(Edge(line.getL0()[i+1],haversine(line.getL0()[i].getLatitude(),line.getL0()[i].getLongitude(),line.getL0()[i+1].getLatitude(),line.getL0()[i+1].getLongitude()),line.getCode()));
                }
                line.setL1(readEachLineFile1(line.getCode()));
                for (int i = 0; i<line.getL1().size()-1;i++){
                    line.getL1()[i].addEdge(Edge(line.getL1()[i+1],haversine(line.getL1()[i].getLatitude(),line.getL1()[i].getLongitude(),line.getL1()[i+1].getLatitude(),line.getL1()[i+1].getLongitude()),line.getCode()));
                }
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
        cout << "This file doesn't exist!" ;
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
        cout  << "This file doesn't exist!"<< endl ;
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



Stop Controller::getClosestStop(double lat1, double lon1) {
    Stop min = stopDB[0];
    for (int i=1;i<stopDB.size();i++){
        if (haversine(lat1,lon1,min.getLatitude(),min.getLongitude())> haversine(lat1,lon1,stopDB[i].getLatitude(),stopDB[i].getLongitude()))
            min = stopDB[i];
    }
    return min;
}

string Controller::getDirections(Stop origin, Stop destination) {
    return "Por aí";
}




 double Controller::haversine(double lat1, double lon1, double lat2, double lon2) {
    // distance between latitudes
    // and longitudes
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
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
