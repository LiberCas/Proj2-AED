

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include "StopEdge.h"

using namespace std;

class Graph {
    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Stop> stops; // The list of nodes being represented

public:
    Graph();
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);
    Stop& getDest(Edge edge);
    void addStop(Stop& stop);
    vector<int> dijkstra_distance (Stop& a, Stop& b);
    vector<int> dijkstra_zones (Stop& a, Stop& b);
    void addEdge(int src, int dest, double weight, string code);
    vector<int> getPath(Stop& a, Stop& b);
    vector<int> bfs(Stop& origin, Stop& dest);
    void resetNodes(int dist);
    Stop& getStop(int index);
    Stop& getStop(string code);
    vector<Stop>& getStops();


};


#endif
