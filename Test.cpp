#include "Graph.h"
#include <iostream>

int main() {
    Graph<std::string> g;
    g.addVertex("V1");
    g.addVertex("V2");
    g.addVertex("v3");
    g.addEdge("V1", "V2");
    std::cout << g;
    return 0;
}