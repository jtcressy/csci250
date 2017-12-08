//
// Created by jtcressy on 12/7/17.
//

#include "Graph.h"
#include <iostream>
#include <sstream>
#include <map>
#include <functional>

template<class T>
void Graph<T>::addNode(int id, T data) {
    if (this->hasNode(id))
        throw std::invalid_argument("Cannot add node '" + std::to_string(id) + "': already exists.");
    Node node;
    node.id = id;
    node.value = data;
    this->nodes.push_back(node);
}

template<class T>
void Graph<T>::addEdge(int id1, int id2, int weight) {
    if (!this->hasNode(id1)) throw std::invalid_argument("Node " + std::to_string(id1) + " does not exist.");
    if (!this->hasNode(id2)) throw std::invalid_argument("Node " + std::to_string(id2) + " does not exist.");
    if (this->hasEdge(id1, id2))
        throw std::invalid_argument("Cannot add edge { " + std::to_string(id1) + ", " + std::to_string(id2) + " }: already exists.");
    Edge edge;
    edge.a = id1;
    edge.b = id2;
    edge.weight = weight;
    this->edges.push_back(edge);
}

template<class T>
void Graph<T>::delNode(int id) {
    if (!this->hasNode(id))
        throw std::invalid_argument("Cannot delete node '" + std::to_string(id) + "': does not exist.");
    for (int i = 0; i < this->nodes.size(); i++) {
        if (this->nodes[i].id == id)
            this->nodes.erase(this->nodes.begin() + i);
    }
}

template<class T>
void Graph<T>::delEdge(int id1, int id2) {
    if (!this->hasEdge(id1, id2))
        throw std::invalid_argument("Cannot delete edge { " + std::to_string(id1) + ", " + std::to_string(id2) + " }: does not exist.");
    this->edges.erase(this->edges.begin() + this->edge_at(id1, id2));
}

template<class T>
bool Graph<T>::hasEdge(int id1, int id2) {
    for (int i = 0; i < this->edges.size(); i++)
        if (this->edges[i].a == id1 && this->edges[i].b == id2)
            return true;
        else if (this->edges[i].a == id2 && this->edges[i].b == id1)
            return true;
    return false;
}

template<class T>
bool Graph<T>::hasNode(int id) {
    for (int i = 0; i < this->nodes.size(); i++)
        if (this->nodes[i].id == id) return true;
    return false;
}

template<class T>
int Graph<T>::edgeWeight(int id1, int id2) {
    return this->edges[this->edge_at(id1, id2)].weight;
}

template<class T>
T Graph<T>::getNode(int id) {
    return this->nodes[id].value;
}

template<class T>
T &Graph<T>::operator[](int id) {
    return this->getNode(id);
}

template<class T>
int Graph<T>::edge_at(int id1, int id2) {
    for (int i = 0; i< this->edges.size(); i++)
        if (this->edges[i].a == id1 && this->edges[i].b == id2)
            return i;
        else if (this->edges[i].a == id2 && this->edges[i].b == id1)
            return i;
    throw std::out_of_range("The specified edge does not exist. { " + std::to_string(id1) + ", " + std::to_string(id2) + " }");
}

// Function readGraph
template<class T>
void Graph<T>::read(std::string line) {
    while (line.length() > 0) {
        if (line.find('(') == std::string::npos) break;
        std::stringstream buf;
        buf << line.substr(line.find('(') + 1, line.find(')'));
        int a, b, weight;
        buf >> a >> b >> weight;
        if (!this->hasNode(a)) this->addNode(a, T());
        if (!this->hasNode(b)) this->addNode(b, T());
        if (!this->hasEdge(a, b)) this->addEdge(a, b, weight);
        line.erase(0, line.find(')') + 1);
    }
}

// Function toString
template<class T>
std::string Graph<T>::print() {
    std::string output;
    output += "{ ";
    for (int i = 0; i < this->nodes.size(); i++) {
        if (i == 0) output += std::to_string(this->nodes[i].id);
        else output += ", " + std::to_string(this->nodes[i].id);
    }
    output += ": ";
    for (int i = 0; i < this->edges.size(); i++) {
        std::string edge =
            std::to_string(this->edges[i].a) + "-" +
            std::to_string(this->edges[i].b) + "(" +
            std::to_string(this->edges[i].weight) + ")";
        if (i == 0) output += edge;
        else output += ", " + edge;
    }
    output += " }";
    return output;
}

template<class T>
std::ostream &operator<<(std::ostream &stream, Graph<T> &graph) {
    stream << graph.print();
    return stream;
}

//Static functions for spanning trees & path trees

template<class T>
Graph<T> Graph<T>::minSpanningTree(Graph<T> graph, int rootNodeID) {
    auto numNodes = (int) graph.nodes.size();
    auto numEdges = (int) graph.edges.size();
    Graph<T> MST; //This will be the constructed MST

    std::map<int, int> keys;
    // keys is a dictionary in which keys are node id's and values are
    // the weight required to reach that node from the root of the MST

    std::map<int, int> parents;
    // parents[x] = y where x is a node ID and y is the ID of the parent of node x

    // for each node in the graph, add to the keys dictionary and set
    // value to INT8_MAX (infinite) except for the root node, since
    // the weight required to reach the root is 0
    for (int i = 0; i < numNodes; i++) keys[graph.nodes[i].id] = INT32_MAX;
    keys[rootNodeID] = 0;

    for (int i = 0; i < numNodes - 1; i++) {
        int minimum = INT32_MAX;
        int minimumID;
        for (auto &key : keys)
            if (!MST.hasNode(key.first) && key.second < minimum)
                minimum = key.second, minimumID = key.first;

        MST.addNode(minimumID, graph.getNode(minimumID));

        for (int j = 0; j < numNodes; j++) {
            int currentNodeID = graph.nodes[j].id;
            if (graph.hasEdge(minimumID, currentNodeID) && !MST.hasNode(currentNodeID) && graph.edgeWeight(minimumID, currentNodeID) < keys[currentNodeID]) {
                // if edge exists in original graph
                // and current node does NOT exist in the MST
                // and this edge's weight is less than our
                // last recorded weight for this node, then
                // save previous node as this node's parent
                parents[currentNodeID] = minimumID;
                // then save the weight between the previous node and the current node
                keys[currentNodeID] = graph.edgeWeight(minimumID, currentNodeID);
                // which is evaluated on the next iteration of this loop.
            }
        }
    }
    // Copy edges from the graph to the MST based on the parents and keys maps.
    // Also ensure that the MST contains all nodes from original graph
    for (int i = 0; i < graph.nodes.size(); i++) {
        if (graph.nodes[i].id == rootNodeID) continue; // root has no parents, so skip it.
        else {
            // an edge will be created between the root node if
            // a node lists the root node as a parent (guaranteed by the algorithm above)
            int parent = parents[graph.nodes[i].id];
            int current = graph.nodes[i].id;
            if (!MST.hasNode(current)) MST.addNode(current, graph.nodes[i].value);
            MST.addEdge(parent, current, graph.edgeWeight(parent, current));
        }
    }
    return MST;
}

template<class T>
int Graph<T>::treeSum(Graph<T> tree) {
    int sum = 0;
    for (int i = 0; i < tree.edges.size(); i++) {
        sum += tree.edges[i].weight;
    }
    return sum;
}

template<class T>
Graph<T> Graph<T>::shortestPathTree(Graph<T> graph, int rootNodeID) {
    auto numNodes = (int) graph.nodes.size();
    auto numEdges = (int) graph.edges.size();
    Graph<T> SPT; //This will be the constructed SPT

    std::map<int, int> dist; //Holds shortest distances from root node to dist[nodeID]

    std::map<int, int> parents;
    // parents[x] = y where x is a node ID and y is the ID of the parent of node x

    // for each node in the graph, add to the dist dictionary and set
    // value to INT8_MAX (infinite) except for the root node, since
    // the weight required to reach the root is 0
    for (int i = 0; i < numNodes; i++) dist[graph.nodes[i].id] = INT32_MAX;
    dist[rootNodeID] = 0;

    for (int i = 0; i < numNodes - 1; i++) {
        int minimum = INT32_MAX;
        int minimumID;
        for (auto &key : dist)
            if (!SPT.hasNode(key.first) && key.second < minimum)
                minimum = key.second, minimumID = key.first;

        SPT.addNode(minimumID, graph.getNode(minimumID));

        for (int j = 0; j < numNodes; j++) {
            int currentNodeID = graph.nodes[j].id;
            if (
                graph.hasEdge(minimumID, currentNodeID)
                && !SPT.hasNode(currentNodeID)
                && dist[minimumID] != INT32_MAX
                && dist[minimumID] + graph.edgeWeight(minimumID, currentNodeID) < dist[currentNodeID]
            ) {
                // if edge exists in original graph
                // and current node does NOT exist in the SPT
                // and weight to current node is not INT32_MAX
                // and total weight from src to current node through the minimum (previous) node
                // is less than the shortest recorded distance to the current node
                // update dist[currentNodeID] so that it reflects the newly found shorter path
                dist[currentNodeID] = dist[minimumID] + graph.edgeWeight(minimumID, currentNodeID);
                parents[currentNodeID] = minimumID;
            }
        }
    }
    // Copy edges from the graph to the SPT based on the parents and keys maps.
    for (int i = 0; i < graph.nodes.size(); i++) {
        if (graph.nodes[i].id == rootNodeID) continue; // root has no parents, so skip it.
        else {
            // an edge will be created between the root node if
            // a node lists the root node as a parent (guaranteed by the algorithm above)
            int parent = parents[graph.nodes[i].id];
            int current = graph.nodes[i].id;
            if (!SPT.hasNode(current)) SPT.addNode(current, graph.nodes[i].value);
            SPT.addEdge(parent, current, graph.edgeWeight(parent, current));
        }
    }
    return SPT;
}

template<class T>
Graph<T> Graph<T>::path(Graph<T> spt, int rootNodeID, int destNodeID) {
    auto numNodes = (int) spt.nodes.size();
    Graph<T> path;
    std::map<int, bool> visited;
    for (auto &node: spt.nodes) visited[node.id] = false;
    Graph<T>::pathhelper(spt, spt._getNode(rootNodeID), spt._getNode(destNodeID), path, visited);
    return path;
}

template<class T>
int Graph<T>::pathLength(Graph<T> path) {
    return Graph<T>::treeSum(path);
}

template<class T>
bool Graph<T>::pathhelper(Graph<T> spt, Graph<T>::Node current, Graph<T>::Node dest, Graph<T> &path, std::map<int, bool> &visited) {
    if (current.id == dest.id) return true; //We found it!
    visited[current.id] = true;
    path.addNode(current.id, current.value);
    std::vector<Graph<T>::Node> connections;
    for (auto &edge: spt.edges) {
        if (edge.a == current.id && !visited[edge.b])
            connections.push_back(
                    spt._getNode(edge.b));
        else if (edge.b == current.id && !visited[edge.a])
            connections.push_back(
                    spt._getNode(edge.a));
    }
    // recurse through all nodes connected to current through an edge
    // until the destination node is found
    for (auto &node: connections) {
        bool result = Graph<T>::pathhelper(spt, node, dest, path, visited);
        if (result) {
            //We found it somewhere down the line
            //copy edge from the shortest path tree
            if (!path.hasNode(node.id)) path.addNode(node.id, node.value);
            path.addEdge(current.id, node.id, spt.edgeWeight(current.id, node.id));
            return true;
        }
    }
    //At this point we didnt find the destination node in any of the connections
    path.delNode(current.id);
    return false;
}

template<class T>
typename Graph<T>::Node Graph<T>::_getNode(int id) {
    for (auto &node: this->nodes) if (node.id == id) return node;
    throw std::invalid_argument("Node with id " + std::to_string(id) + " does not exist in the graph.");
}
