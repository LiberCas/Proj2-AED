//
// Created by igcbs on 16/01/2022.
//

#include "StopEdge.h"
#include <iostream>

Stop::Stop() {
    this->code = "";
    this->name = "";
    this->zone = "";
    this->latitude = 0;
    this->longitude = 0;

}
Stop::Stop(const string &code, const string &name, const string &zone, float latitude, float longitude) {
    this->code = code;
    this->name = name;
    this->zone = zone;
    this->latitude = latitude;
    this->longitude =longitude;
}

Stop::~Stop(){
    code.clear();
    name.clear();
    zone.clear();
}

const string &Stop::getCode() const {
    return code;
}

const string &Stop::getName() const {
    return name;
}

const string &Stop::getZone() const {
    return zone;
}

float Stop::getLatitude() const {
    return latitude;
}

float Stop::getLongitude() const {
    return longitude;
}

void Stop::setCode(const string &code) {
    Stop::code = code;
}

void Stop::setName(const string &name) {
    Stop::name = name;
}

void Stop::setZone(const string &zone) {
    Stop::zone = zone;
}

void Stop::setLatitude(float latitude) {
    Stop::latitude = latitude;
}

void Stop::setLongitude(float longitude) {
    Stop::longitude = longitude;
}

istream & operator>>(istream &is, Stop &stop) {
    char temp[256];
    if(!is.getline(temp, 100, ',')){
        is.ignore();
        return is;
    }
    stop.setCode((string)temp);
    is.getline(temp, 100, ',');
    stop.setName((string)temp);
    is.getline(temp, 100, ',');
    stop.setZone((string)temp);
    is.getline(temp, 100, ',');
    stop.setLatitude(stof(temp));
    is.getline(temp, 100);
    stop.setLongitude(stof(temp));
    return is;
}

Stop::Stop(int latitude, int longitude) {
    this->latitude = latitude;
    this->longitude =longitude;
}

void Stop::addEdge(Edge edge) {
    adj.push_back(edge);
}

void Stop::setDistance(double distance) {
    this->distance=distance;
}

void Stop::setVisited(bool visited) {
    this->visited=visited;
}

void Stop::setPred(string pred){
    this->pred=pred;
}

int Stop::getDistance() const {
    return distance;
}

bool Stop::getVisited() const {
    return visited;
}

const list<struct Edge> & Stop::getAdj() const {
    return adj;
}

//----------------------------------------------------------------------------------------------


Edge::Edge(Stop dest, double weight, string lineCode) {
    this->weight=weight;
    this->lineCode=lineCode;
    this->dest=dest;
}

 Stop Edge::getDest() const {
    return dest;
}

string Edge::getLineCode() {
    return lineCode;
}

int Edge::getWeight() const {
    return weight;
}

void Edge::setDest(Stop dest) {
    this->dest =dest;
}

void Edge::setLineCode(string lineCode) {
    this->lineCode=lineCode;
}

void Edge::setWeight(int weight) {
    this->weight=weight;
}