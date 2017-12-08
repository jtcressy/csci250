#include <iostream>
#include <string>
#include <fstream>
#include "Graph.cpp"
using namespace std;

int main() {
    typedef Graph<string> graph_t;
    graph_t graph10;
    graph_t graph100;
    ifstream ten("graph10.txt");
    ifstream hundred("graph100.txt");
    while (!ten.eof()) {
        string line;
        getline(ten, line);
        graph10.read(line);
    }
    while (!hundred.eof()) {
        string line;
        getline(hundred, line);
        graph100.read(line);
    }
    cout << "With graph10.txt" << endl;
    [](graph_t &graph) {
        cout << "base graph: " << graph << endl;
        graph_t MST = graph_t::minSpanningTree(graph, 0);
        cout << "MST at vertex 0: " << MST << endl;
        cout << "Sum of all edges: " << graph_t::treeSum(MST) << endl;
        graph_t SPT = graph_t::shortestPathTree(graph, 1);
        cout << "SPT at vertex 1: " << SPT << endl;
        cout << "Sum of all edges: " << graph_t::treeSum(SPT) << endl;
        graph_t path = graph_t::path(SPT, 1, 7);
        cout << "Path from 1 to 7: " << path << endl;
        cout << "Weight of path: " << graph_t::pathLength(path) << endl;
    }(graph10);

    [](graph_t &graph) {
        cout << endl << "With graph100.txt" << endl;
        cout << "base graph: " << graph << endl;
        graph_t MST = graph_t::minSpanningTree(graph, 3);
        cout << "MST at vertex 3: " << MST << endl;
        cout << "Sum of all edges: " << graph_t::treeSum(MST) << endl;
        graph_t SPT = graph_t::shortestPathTree(graph, 2);
        cout << "SPT at vertex 2: " << SPT << endl;
        cout << "Sum of all edges: " << graph_t::treeSum(SPT) << endl;
        graph_t path = graph_t::path(SPT, 2, 87);
        cout << "Path from 2 to 87: " << path << endl;
        cout << "Total weight of path: " << graph_t::pathLength(path) << endl;
    }(graph100);
    return 0;
}