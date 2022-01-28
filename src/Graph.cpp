//
// Created by 35196 on 24/01/2022.
//


#include "Graph.h"
#include "minHeap.h"

Graph::Graph() {
    this->n=0;
    stops={};
}
// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir){}

void Graph::addStop(Stop &stop) {
    this->stops.push_back(stop);
}
// Add edge from source to destination with a certain weight

vector<int> Graph::dijkstra_distance(Stop& a, Stop& b) {
    vector<int> res;
    if (a==b) return {};
    for(int i = 0; i <= n; i++) {
        stops[i].setDistance(1000);
        stops[i].setVisited(false);
    }
    a.setDistance(0);
    a.setPred(a.getIndex());
    MinHeap<int,double> q(n,NULL);
    for (int i = 0; i<=n;i++){
        q.insert(i,stops[i].getDistance());
    }
    while (q.getSize()!=0){
        int u = q.removeMin();
        stops[u].setVisited(true);
        for (Edge& edge : stops[u].getAdj()){
            double tempDist = stops[u].getDistance() + edge.getWeight();
            if ((tempDist < getDest(edge).getDistance()) && q.hasKey(edge.getDest())){
                stops[getDest(edge).getIndex()].setDistance(tempDist);
                stops[getDest(edge).getIndex()].setPred(u);
                q.decreaseKey(getDest(edge).getIndex(),tempDist);
            }
        }
    }
    res.push_back(b.getIndex());
    int i = b.getPred();
    while (i!=a.getIndex()){
        res.insert(res.begin(),i);
        i = getStop(i).getPred();
    }
    res.insert(res.begin(), a.getIndex());

    if (b.getDistance()==INT_MAX) return {};
    return res;
}

Stop& Graph::getDest(Edge edge){
    return(stops.at(edge.getDest()));

}

int Graph::getIndexStop(string code) {
    for(int i=0;i<=n;i++){
        if(stops[i].getCode()==code){
            return i;
        }
    }
    return -1;
}

Stop &Graph::getStop(int index) {
    for(int i=0;i<n;i++){
        if(stops.at(i).getIndex() == index)
            return stops.at(i);
    }
}
Stop& Graph::getStop(string code){
    for(int i=0;i<n;i++){
        if(stops.at(i).getCode() == code)
            return stops.at(i);
    }
}

vector<Stop>& Graph::getStops(){
    return stops;
}

void Graph::addEdge(int src, int dest, double weight = 1.0, string code=0){
    stops.at(src).addEdge(dest, weight, code);
}



/*
// Depth-First Search: example implementation
void Graph::dfs(Stop& w) {
    w.setVisited(true) ;
    for (auto &e : w.getAdj()) {
        Stop w = e.getDest();
        if (w.getVisited())
            dfs(w);
    }
}

// Depth-First Search: example implementation
void Graph::bfs(Stop& x) {
    for (int v=1; v<=n; v++) stops[v].setVisited(false);
    queue<Stop> q; // queue of unvisited nodes
    q.push(x);
    x.setVisited(true);
    while (!q.empty()) { // while there are still unvisited nodes
        Stop u = q.front(); q.pop();
        for (auto e : u.getAdj()) {
            Stop w = e.getDest();
            if (!w.getVisited()) {
                q.push(w);
                w.setVisited(true);
            }
        }
    }
}



// ----------------------------------------------------------
// Exercicio 2: Componentes conexos
// ----------------------------------------------------------

// ..............................
// a) Contando componentes conexos
// TODO
int Graph::connectedComponents() {
    for (int v=1; v<=n; v++) stops[v].setVisited(false);
    int res = 0;
    for (int i=1 ; i<n;i++){
        if (!stops[i].getVisited()){
            res++;
            visitando(stops[i]);
        }
    }
    return res;
}

void Graph::visitando(Stop& v){
    v.setVisited(true);
    for (auto e : v.getAdj()) {
        Stop w = e.getDest();
        if (!w.getVisited())
            visitando(w);
    }
}


// ----------------------------------------------------------
// Exercicio 3: Ordenacao topologica
// ----------------------------------------------------------
// TODO
list<Stop> Graph::topologicalSorting() {
    list<Stop> order;
    for(int i = 1; i <= n; i++)
        stops[i].setVisited(false);
    for(int i = 1; i <= n; i++){
        if(!stops[i].getVisited()){
            dfsTopo(stops[i], order);
        }
    }
    return order;
}
void Graph::dfsTopo(Stop& v, list<Stop>& order) {
    v.setVisited(true);
    for(auto &e : v.getAdj()){
        Stop w = e.getDest();
        if(!w.getVisited())
            dfsTopo(w, order);
    }
    order.push_front(v);
}

// ..............................
// a) Distancia entre dois nos
// TODO
int Graph::distance(Stop a, Stop b) {
    if(a == b) return 0;
    for(int i = 1; i <= n; i++)
        stops[i].setDistance(-1);
    bfsDist(a);
    return b.getDistance();
}
void Graph::bfsDist(Stop x){
    x.setDistance(0);
    for (int v=1; v<=n; v++) stops[v].setVisited(false);
    queue<Stop> q; // queue of unvisited nodes
    q.push(x);
    x.setVisited(true);
    while (!q.empty()) { // while there are still unvisited nodes
        Stop u = q.front(); q.pop();
        for (auto &e : u.getAdj()) {
            Stop w = e.getDest();
            if (!w.getVisited()) {
                q.push(w);
                w.setVisited(true);
                w.setDistance(u.getDistance()+1);
            }
        }
    }

}




*/

