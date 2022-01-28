//
// Created by igcbs on 16/01/2022.
//

#ifndef STOPEDGE_H
#define STOPEDGE_H

#include <string>
#include <list>

using namespace std;

class Edge;

class Stop {
private:
    int index;
    string code;
    string name;
    string zone;
    float latitude;
    float longitude;
    list<Edge> adj;
    double distance;
    bool visited;   // As the node been visited on a search?
    int pred;

public:
    Stop();
    Stop(const string &code, const string &name, const string &zone, float latitude, float longitude);
    ~Stop();
    void setIndex(int index);
    const string &getCode() const;
    const string &getName() const;
    const string &getZone() const;
    float getLatitude() const;
    float getLongitude() const;
    int getPred( ) const    ;
    double getDistance()const;
    bool getVisited() const;
    list<Edge> getAdj();
    void setCode(const string &code);
    void setDistance(double distance);
    void setVisited(bool visited);
    void setPred(int pred);
    void setName(const string &name);
    void setZone(const string &zone);
    void setLatitude(float latitude);
    void setLongitude(float longitude);
    friend istream &operator>>(istream &is, Stop &stop);
    void addEdge(Edge& edge);
    Stop(int x, int y);
    friend bool operator==(const Stop& s1, const Stop& s2){
        return (s1.code==s2.code);
    }

    int getIndex() const;
    void addEdge(int dest, double weight, string code);
};


using namespace std;
class Edge{
private:
    int dest;   // Destination node
    double weight; // An integer weight
    string lineCode;
public:
    Edge(int dest, double weight, string lineCode);
    int getDest();
    double getWeight() const;
    string getLineCode();
    void setDest(int dest);
    void setWeight(double weight);
    void setLineCode(string lineCode);
    friend bool operator==(const Edge& e1, const Edge& e2){
        return(e1.weight==e2.weight && e1.lineCode==e2.lineCode && e1.dest==e2.dest);
    }

};

#endif //STOP_&_EDGE_H
