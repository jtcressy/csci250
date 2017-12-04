//
// Created by jtcressy on 11/13/17.
//
#include <string>
#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H


class Graph {
private:
    int** matrix;
    bool* vertices;
    int maxvertices;
    bool validateInput(int vertex1, int vertex2);

public:
    Graph();
    void addVertex (int vertex);
    void addEdge (int vertex1, int vertex2, int weight);
    void removeEdge (int vertex1, int vertex2);
    void removeVertex (int vertex);
    bool isEdge (int vertex1, int vertex2);
    int edgeWeight (int vertex1, int vertex2);
    bool isNeighbor (int vertex1, int vertex2);
    std::string toString ();
};


#endif //GRAPHS_GRAPH_H
