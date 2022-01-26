//
// Created by 35196 on 26/01/2022.
//

#ifndef EDGE_H
#define EDGE_H
#include "string"

using namespace std;

class Edge{
private:
    string dest;   // Destination node
    int weight; // An integer weight
    string lineCode;
public:
    Edge(string dest,int weight, string lineCode);
    string getDest();
    int getWeight();
    string getLineCode();
    void setDest(string dest);
    void setWeight(int weight);
    void setLineCode(string lineCode);


};
#endif EDGE_H
