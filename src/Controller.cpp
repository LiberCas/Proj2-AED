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
    readStops();
    readLines();
}

void Controller::readStops(){
    graph = Graph(2487, true);
    ifstream stopsFile;
    stopsFile.open("../src/dataset/stops.csv");
    if (stopsFile.fail()) {
        cout << "This file doesn't exist!\n";
    } else {
        string line;
        stopsFile >> line;
        stopsFile.ignore();
        int index=0;
        while (!stopsFile.eof() && stopsFile.peek()!='\n') {
            Stop stop;
            stopsFile >> stop;
            stop.setIndex(index);
            this->stopDB.push_back(stop);
            graph.getStops().push_back(stop);
            index++;
        }
        stopDB.pop_back();
    }
    stopsFile.close();
    /*
    for (int i=0;i<stopDB.size();i++){
        graph.addStop(stopDB.at(i));
    }
    */
}

void Controller::readLines() {
    ifstream linesFile;
    linesFile.open("../src/dataset/lines.csv");
    if (linesFile.fail()) {
        cout << "This file doesn't exist!\n";
    }
    else {
        string l;
        linesFile >> l;
        linesFile.ignore();
        while (!linesFile.eof() && linesFile.peek() != '\n') {
            Line line;
            linesFile >> line;
            if(line.getCode().find('M') == string::npos)
                this->linesDB.push_back(line);
        }
        linesDB.pop_back();
        linesFile.close();
        extractStopsFromLines();
    }
}



int Controller::getIndexStop(string code) {
    for(int i=0;i<=stopDB.size();i++){
        if(stopDB[i].getCode()==code){
            return i;
        }
    }
    return -1;
}

void Controller::extractStopsFromLines(){
    for(int i=0; i<linesDB.size(); i++){
        ifstream individLinesFile;
        string code = linesDB[i].getCode();
        individLinesFile.open("../src/dataset/line_" + code + "_0.csv");
        string prevStopCode, nextStopCode;
        getline(individLinesFile, prevStopCode);
        getline(individLinesFile, prevStopCode);
        int prevStop = getIndexStop(prevStopCode);
        while(getline(individLinesFile, nextStopCode)){
            int nextStop = getIndexStop(nextStopCode);
            double weight=haversine(graph.getStops()[prevStop].getLatitude(), graph.getStops()[prevStop].getLongitude(), graph.getStops()[nextStop].getLatitude(), graph.getStops()[nextStop].getLongitude());
            graph.addEdge(prevStop,nextStop,weight, code);
            linesDB.at(i).getL0().push_back(prevStop);
            prevStop=nextStop;
        }
        linesDB.at(i).getL0().push_back(prevStop);
        individLinesFile.close();
        individLinesFile.open("../src/dataset/line_" + code + "_1.csv");
        if(individLinesFile.peek()!='0') {
            getline(individLinesFile, prevStopCode);
            getline(individLinesFile, prevStopCode);
            prevStop = getIndexStop(prevStopCode);
            while(getline(individLinesFile, nextStopCode)){
                int nextStop = getIndexStop(nextStopCode);
                double weight= haversine(graph.getStops()[prevStop].getLatitude(), graph.getStops()[prevStop].getLongitude(), graph.getStops()[nextStop].getLatitude(), graph.getStops()[nextStop].getLongitude());
                graph.addEdge(prevStop,nextStop,weight, code);
                linesDB.at(i).getL1().push_back(prevStop);
                prevStop=nextStop;
            }
            linesDB.at(i).getL1().push_back(prevStop);
        }
        individLinesFile.close();
    }
}

bool Controller::readUserData() {
    ifstream userFile;
    userFile.open("../src/dataset/userData.txt");
    if (userFile.fail()) {
        return false;
    }
    char buf[256];
    userFile.getline(buf, 100);
    userName = buf;
    userFile.ignore();
    userFile.getline(buf, 100);
    walkingFactor = atoi(buf);
    userFile.ignore();
    userFile.getline(buf, 100);
    maxWalingDistance = atoi(buf);
    userFile.close();
    return true;
}

Controller::~Controller(){
    stopDB.clear();
    linesDB.clear();
}

vector<Line> Controller::getLines() {
    return linesDB;
}

vector<Stop>& Controller::getStops() {
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

string Controller::getDirections(string origin, string destination) {/*
    vector<pair<int, string>> temp = graph.dijkstra_distance(graph.getStop("CORD2"), graph.getStop("GDM1"));
    for (int i = 0;i<temp.size();i++){
        cout << stopDB[temp[i].first].getCode() << " " << temp[i].second << endl;
    }*/
    vector<pair<int, string>> path = graph.dijkstra_distance(graph.getStop(origin), graph.getStop(destination));
    string line = path[1].second;
    string directions = "From " + stopDB[path[0].first].getName() + " in line " + line + " to ";
    for (int i = 1; i < path.size(); ++i) {
        if(path[i].second!=line){
            line = path[i].second;
            directions += stopDB[path[i-1].first].getName() + "\nFrom " + stopDB[path[i-1].first].getName() + " in line " + path[i].second +" to ";
        }
    }
    directions += graph.getStop(destination).getName();
    return directions;
}


vector<Stop> &Controller::getStopDB() {
    return this->stopDB;
}

string Controller::getUsername(){
    return userName;
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
    ofstream userFile;
    userFile.open("../src/dataset/userData.txt");
    userFile << userName << "\n" << walkingFactor << "\n" << maxWalingDistance;
}

void Controller::setUsername(string username) {
    this->userName = username;
}

void Controller::setMaxWalkDist(int maxWD) {
    maxWalingDistance = maxWD;
}

void Controller::setWalkingFac(int walkF) {
    walkingFactor = (25-walkF)/10;
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

/*else if (line.getCode() == "300" || line.getCode() == "301" || line.getCode() == "302" ||
                 line.getCode() == "303") {
            line.setL0(readEachLineFile0(line.getCode()));
            for (int i = 0; i < line.getL0().size() - 1; i++) {
                line.getL0()[i].addEdge(Edge(line.getL0()[i + 1],
                                             haversine(line.getL0()[i].getLatitude(), line.getL0()[i].getLongitude(),
                                                       line.getL0()[i + 1].getLatitude(),
                                                       line.getL0()[i + 1].getLongitude()), line.getCode()));
            }
        }
 * line.setL0(readEachLineFile0(line.getCode()));
            for (int i = 0; i < line.getL0().size() - 1; i++) {
                line.getL0()[i].addEdge(Edge(line.getL0()[i + 1],
                                             haversine(line.getL0()[i].getLatitude(), line.getL0()[i].getLongitude(),
                                                       line.getL0()[i + 1].getLatitude(),
                                                       line.getL0()[i + 1].getLongitude()), line.getCode()));
            }
            line.setL1(readEachLineFile1(line.getCode()));
            for (int i = 0; i < line.getL1().size() - 1; i++) {
                line.getL1()[i].addEdge(Edge(line.getL1()[i + 1],
                                             haversine(line.getL1()[i].getLatitude(), line.getL1()[i].getLongitude(),
                                                       line.getL1()[i + 1].getLatitude(),
                                                       line.getL1()[i + 1].getLongitude()), line.getCode()));
            }
 */
