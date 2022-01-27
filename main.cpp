#include <iostream>
#include "src/Interface/System.h"

int main() {
    System system = System();
    double temp = system.getController().getGraph().dijkstra_distance(system.getController().getStops()[2], system.getController().getStops()[3]);
    return 0;
}
