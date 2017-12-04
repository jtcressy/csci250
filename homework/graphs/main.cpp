#include <iostream>
#include "Graph.h"
using namespace std;

int main() {
    Graph g1;
    g1.addVertex(0);
    g1.addVertex(1);
    g1.addVertex(2);
    g1.addVertex(3);
    g1.addEdge(0, 1, 13);
    g1.addEdge(1, 2, 20);
    g1.addEdge(1, 3, 11);
    g1.addEdge(2, 3, 53);
    cout << "g1: " << g1.toString() << endl;
    Graph g2;
    g2.addVertex(1);
    g2.addVertex(2);
    g2.addVertex(3);
    g2.addVertex(4);
    g2.addVertex(5);
    g2.addVertex(6);
    g2.addEdge(1, 2, 13);
    g2.addEdge(2, 3, 20);
    g2.addEdge(2, 4, 11);
    g2.addEdge(3, 4, 53);
    g2.addEdge(1, 6, 40);
    g2.addEdge(2, 5, 33);
    cout << "g2: " << g2.toString() << endl;
    g2.removeEdge(2, 4);
    g2.removeEdge(3, 4);
    g2.removeVertex(4);
    cout << "*delete vertex 4 and edges 2-4 and 3-4*" << endl;
    cout << "g2: " << g2.toString() << endl;
    return 0;
}