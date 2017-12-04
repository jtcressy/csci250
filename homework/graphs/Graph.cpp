//
// Created by jtcressy on 11/13/17.
//

#include "Graph.h"
#include <string>
#include <sstream>
using namespace std;


Graph::Graph() {
    maxvertices = 100;
    matrix = new int*[maxvertices];
    for(int i = 0; i < maxvertices; i++) {
        matrix[i] = new int[maxvertices];
        for(int j = 0; j < maxvertices; j++) matrix[i][j] = 0;
    }
    vertices = new bool[maxvertices];
    for(int i = 0; i < maxvertices; i++) vertices[i] = false;
}

void Graph::addVertex(int vertex) {
    vertices[vertex] = true;
}

void Graph::addEdge(int vertex1, int vertex2, int weight) {
    if (this->validateInput(vertex1, vertex2)) {
        if (weight <= 0)
            throw "Invalid weight '" + to_string(weight) + "' for creating edge. weight >= 1";
        matrix[vertex1][vertex2] = weight;
    }
}

void Graph::removeEdge(int vertex1, int vertex2) {
    if (this->validateInput(vertex1, vertex2)) {
        matrix[vertex1][vertex2] = 0;
    }
}

void Graph::removeVertex(int vertex) {
    vertices[vertex] = false;
}

bool Graph::isEdge(int vertex1, int vertex2) {
    if (this->validateInput(vertex1, vertex2)) if (matrix[vertex1][vertex2] > 0) return true;
    return false;
}

int Graph::edgeWeight(int vertex1, int vertex2) {
    if (this->validateInput(vertex1, vertex2)) return this->matrix[vertex1][vertex2];
    return 0;
}

bool Graph::isNeighbor(int vertex1, int vertex2) {
    return this->isEdge(vertex1, vertex2);
}

string Graph::toString() {
    stringstream ss;
    ss << "{";
    int j = 0;
    for(int i = 0; i < maxvertices; i++) {
        if (vertices[i]) {
            if (j == 0) ss << to_string(i);
            else ss << ", " + to_string(i);
            j++;
        }
    }
    ss << ": ";
    int l = 0;
    for(int i = 0; i < maxvertices; i++) {
        for(int k = 0; k < maxvertices; k++) {
            if(i!=k && vertices[i] && vertices[k]) {
                if (this->isEdge(i, k)) {
                    if (l == 0) ss << to_string(i) + "-" + to_string(k) + "(" + to_string(this->edgeWeight(i, k)) + ")";
                    else ss << ", " + to_string(i) + "-" + to_string(k) + "(" + to_string(this->edgeWeight(i, k)) + ")";
                    l++;
                }
            }
        }
    }
    ss << "}";
    return ss.str();
}

bool Graph::validateInput(int vertex1, int vertex2) {
    if (vertex1 == vertex2) throw "Loopback Edges Not Supported!";
    if (!vertices[vertex1]) throw "Vertex '" + to_string(vertex1) + "' does not exist in the graph";
    if (!vertices[vertex2]) throw "Vertex '" + to_string(vertex2) + "' does not exist in the graph";
    return true;
}
