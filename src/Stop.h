//
// Created by igcbs on 16/01/2022.
//

#ifndef UNTITLED_STOP_H
#define UNTITLED_STOP_H

#include <string>
#include <list>
#include "Edge.h"

using namespace std;

class Stop {
private:
    string code;
    string name;
    string zone;
    float latitude;
    float longitude;
    list<Edge> adj;
    int distance;
    bool visited;   // As the node been visited on a search?

public:
    Stop();
    Stop(const string &code, const string &name, const string &zone, float latitude, float longitude);
    ~Stop();
    const string &getCode() const;
    const string &getName() const;
    const string &getZone() const;
    float getLatitude() const;
    float getLongitude() const;
    void setCode(const string &code);
    void setDistance(int distance);
    void setVisited(bool visites);
    void setName(const string &name);
    void setZone(const string &zone);
    void setLatitude(float latitude);
    void setLongitude(float longitude);
    friend istream &operator>>(istream &is, Stop &stop);
    void addEdge(Edge edge);
    Stop(int x, int y);
};


#endif //UNTITLED_STOP_H
