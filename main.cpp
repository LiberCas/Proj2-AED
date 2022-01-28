#include <iostream>
#include "src/Interface/System.h"

int main() {
    System system = System();
    vector<int> temp = system.getController().getGraph().dijkstra_distance(system.getController().getGraph().getStop("AMRQ3"), system.getController().getGraph().getStop("OUTE1"));
    for (int i = 0;i<temp.size();i++){
        cout << system.getController().getStopDB()[temp[i]].getCode() << endl;
    }
    cout << "\n";
    temp = system.getController().getGraph().bfs(system.getController().getGraph().getStop("AMRQ3"), system.getController().getGraph().getStop("OUTE1"));
    for (int i = 0;i<temp.size();i++){
        cout << system.getController().getStopDB()[temp[i]].getCode() << endl;
    }
    cout << "\n";
    temp = system.getController().getGraph().dijkstra_zones(system.getController().getGraph().getStop("AMRQ2"), system.getController().getGraph().getStop("OUTE2"));
    for (int i = 0;i<temp.size();i++){
        cout << system.getController().getStopDB()[temp[i]].getCode() << endl;
    }
    return 0;
}
