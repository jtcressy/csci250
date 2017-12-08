//
// Created by jtcressy on 12/7/17.
//

#ifndef TEMPLATEGRAPH_GRAPH_H
#define TEMPLATEGRAPH_GRAPH_H
#include <stdexcept>
#include <vector>
#include <string>
#include <map>


template <class T>
class Graph {
private:
    struct Edge {
        int weight;
        int a;
        int b;
    };
    typedef std::vector<Edge> Edge_list_t;
    struct Node {
        int id;
        T value;
    };
    typedef std::vector<Node> Node_list_t;
    Edge_list_t edges;
    Node_list_t nodes;
    int edge_at(int id1, int id2);
public:
    void addNode (int id, T data);
    void addEdge (int id1, int id2, int weight);
    void delNode (int id);
    void delEdge (int id1, int id2);
    bool hasEdge (int id1, int id2);
    bool hasNode (int id);
    int edgeWeight(int id1, int id2);
    T getNode(int id);
private:
    Node _getNode(int id);
public:
    T& operator[] (int id);
    void read(std::string line);
    std::string print();
    template<class Y>
    friend std::ostream& operator<< (std::ostream& stream, Graph<Y> &graph);
    //spanning&path trees
    static Graph<T> minSpanningTree (Graph<T> graph, int rootNodeID);
    static int treeSum(Graph<T> tree);
    static Graph<T> shortestPathTree (Graph<T> graph, int rootNodeID);
    static Graph<T> path (Graph<T> spt, int rootNodeID, int destNodeID);
    static int pathLength (Graph<T> path);
private:
    static bool pathhelper (Graph<T> spt, Graph<T>::Node srcid, Graph<T>::Node destid, Graph<T>& path, std::map<int, bool> &visited);
};




#endif //TEMPLATEGRAPH_GRAPH_H
