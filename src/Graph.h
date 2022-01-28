

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
    double dijkstra_distance (Stop& a, Stop& b);
    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, double weight, string code);

    // Depth-First Search: example implementation
    void dfs(Stop& v);

    // Breadth-First Search: example implementation
    void bfs(Stop& v);

    // ----- Functions to implement in this class -----
    int connectedComponents();
    list<Stop> topologicalSorting();
    int distance(Stop a, Stop b);
    void visitando(Stop& v);
    void dfsTopo(Stop& v, list<Stop>& order);
    void bfsDist(Stop v);

    Stop& getStop(string code);
    vector<Stop>& getStops();
    int getIndexStop(string code);


};

#endif
