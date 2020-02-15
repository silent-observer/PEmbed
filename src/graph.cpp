#include "graph.hpp"

void Graph::addNode(double x, double y) {
    int id = 1;
    for (auto i = nodes.begin(); i != nodes.end(); i++)
    {
        if (i->first != id) break;
        id++;
    }
    
    Node node(x, y);
    nodes[id] = node;
}

void Graph::removeNode(int id) {
    if (!nodes.count(id)) 
        return;

    auto i = edges.begin();
    while (i != edges.end())
    {
        if (i->id1 == id || i->id2 == id)
            i = edges.erase(i);
        else
            i++;
    }
    nodes.erase(id);
};
void Graph::addEdge(int id1, int id2) {
    if (!nodes.count(id1) || !nodes.count(id2)) 
        return;

    
    for (auto i = edges.begin(); i != edges.end(); i++)
        if (i->id1 == id1 && i->id2 == id2)
            return;
    edges.push_back({id1, id2});
}
void Graph::removeEdge(int id1, int id2) {
    if (!nodes.count(id1) || !nodes.count(id2)) 
        return;

    for (auto i = edges.begin(); i != edges.end(); i++)
        if (i->id1 == id1 && i->id2 == id2) {
            edges.erase(i);
            return;
        }
}
void Graph::moveNode(int id, double x, double y) {
    if (!nodes.count(id)) 
        return;
    nodes[id].x = x;
    nodes[id].y = y;
}

int Graph::findNode(double x, double y) {
    for (auto i = nodes.begin(); i != nodes.end(); i++)
    {
        double x1 = i->second.x;
        double y1 = i->second.y;
        double distSquared = (x1 - x) * (x1 - x) + (y1 - y) * (y1 - y);
        if (distSquared < NODE_RADIUS * NODE_RADIUS) {
            return i->first;
        }
    }
    return 0;
}