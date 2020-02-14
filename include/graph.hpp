#pragma once

#include <vector>
#include <map>

const double NODE_RADIUS = 5;

struct Node {
    double x;
    double y;
    std::vector<int> edges;

    Node(double x, double y) : x(x), y(y) {}
};

class Graph {
private:
    std::map<int, Node> nodes;
public:
    void addNode(double x, double y);
    void removeNode(int id);
    void addEdge(int id1, int id2);
    void removeEdge(int id1, int id2);
    void moveNode(int id, double x, double y);

    int findNode(double x, double y);
    Node& getNode(int id);
};