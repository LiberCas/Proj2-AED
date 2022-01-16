//
// Created by igcbs on 16/01/2022.
//

#include "Stop.h"

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
    is.getline(temp, 100, ',');
    stop.setCode((string)temp);
    is.getline(temp, 100, ',');
    stop.setName((string)temp);
    is.getline(temp, 100, ',');
    stop.setZone((string)temp);
    is.getline(temp, 100, ',');
    stop.setLatitude(stof(temp));
    is.getline(temp, 100, ',');
    stop.setLongitude(stof(temp));
    is.ignore();
    return is;
}
