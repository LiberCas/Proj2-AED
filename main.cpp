#include <iostream>
#include "src/Interface/System.h"

int main() {
    System system = System();
    vector<pair<int, string>> temp = system.getController().getGraph().dijkstra_distance(system.getController().getGraph().getStop("AV1"), system.getController().getGraph().getStop("BLD1"));
    for (int i = 0;i<temp.size();i++){
        cout << system.getController().getStopDB()[temp[i].first].getCode() << " " << temp[i].second << endl;
    }
    return 0;
}
