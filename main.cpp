#include <iostream>
#include "src/Interface/System.h"

int main() {
    System system = System();
    double temp = system.getController().getGraph().dijkstra_distance(system.getController().getGraph().getStop("CORD2"), system.getController().getGraph().getStop("GDM1"));
    return 0;
}
