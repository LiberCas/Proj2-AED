//
// Created by 35196 on 24/01/2022.
//


#include "Graph.h"
#include "minHeap.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), stops(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, string dest, int weight,string code) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    stops[src].addEdge(Edge(dest,weight,code));
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}

// Depth-First Search: example implementation
void Graph::dfs(int v) {
    cout << v << " "; // show node order
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfs(w);
    }
}

// Depth-First Search: example implementation
void Graph::bfs(int v) {
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v]. visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        cout << u << " "; // show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
            }
        }
    }
}

// ----------------------------------------------------------
// Exercicio 1: Introdução a uma classe simplificada de grafos
// ----------------------------------------------------------

// ..............................
// a) Contando diferentes somas de pares
// TODO
int Graph::outDegree(int v) {
    if (v>n||v==0)
        return -1;
    else
        return nodes[v].adj.size();
}

// ----------------------------------------------------------
// Exercicio 2: Componentes conexos
// ----------------------------------------------------------

// ..............................
// a) Contando componentes conexos
// TODO
int Graph::connectedComponents() {
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    int res = 0;
    for (int i=1 ; i<n;i++){
        if (!nodes[i]. visited){
            res++;
            visitando(i);
        }
    }
    return res;
}

void Graph::visitando(int v){
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            visitando(w);
    }
}
// ..............................
// b) Componente gigante
// TODO
int Graph::giantComponent() {
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    int res = 0;
    for (int i=1 ; i<n;i++){
        if (!nodes[i]. visited){
            res = max(res,conta(i));
        }
    }
    return res;

}
int Graph::conta(int v){
    int res=1;
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            res += conta(w);
    }
    return res;
}


// ----------------------------------------------------------
// Exercicio 3: Ordenacao topologica
// ----------------------------------------------------------
// TODO
list<int> Graph::topologicalSorting() {
    list<int> order;
    for(int i = 1; i <= n; i++)
        nodes[i].visited = false;
    for(int i = 1; i <= n; i++){
        if(!nodes[i].visited){
            dfsTopo(i, order);
        }
    }
    return order;
}
void Graph::dfsTopo(int v, list<int>& order) {
    nodes[v].visited = true;
    for(auto e : nodes[v].adj){
        int w = e.dest;
        if(!nodes[w].visited)
            dfsTopo(w, order);
    }
    order.push_front(v);
}

// ----------------------------------------------------------
// Exercicio 4: Distancias em grafos nao pesados
// ----------------------------------------------------------

// ..............................
// a) Distancia entre dois nos
// TODO
int Graph::distance(int a, int b) {
    if(a == b) return 0;
    for(int i = 1; i <= n; i++)
        nodes[i].distance = -1;
    bfsDist(a);
    return nodes[b].distance;
}
void Graph::bfsDist(int v){
    nodes[v].distance = 0;
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v]. visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        cout << u << " "; // show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
            }
        }
    }

}
// ..............................
// b) Diametro
// TODO
int Graph::diameter() {
    if (connectedComponents() > 1) return -1;
    else{
        bfsDist(1);
        int d = 0;
        for(int i = 1; i <= n; i++)
            d = max(d, nodes[i].distance);
        return d;
    }
}

int Graph::dijkstra_distance(int a, int b) {
    if (a==b) return 0;
    for(int i = 1; i <= n; i++) {
        nodes[i].distance=INT_MAX;
        nodes[i].visited= false;
    }
    nodes[a].distance=0;
    MinHeap<int,int> q(n,INT_MIN);
    for (int i = 1; i<=n;i++){
        q.insert(i,nodes[i].distance);
    }
    while (q.getSize()!=0){
        int u = q.removeMin();
        nodes[u].visited= true;
        for (auto & edge : nodes[u].adj){
            if ( (nodes[u].distance + edge.weight < nodes[edge.dest].distance) && q.hasKey(edge.dest)  ){
                nodes[edge.dest].distance=nodes[u].distance + edge.weight;
                q.decreaseKey(edge.dest,nodes[edge.dest].distance);
            }
        }

    }
    if (nodes[b].distance==INT_MAX) return -1;
    return nodes[b].distance;
}


