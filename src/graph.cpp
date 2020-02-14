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
    std::vector<Edge>& edges = nodes[id].edges;
    for (int i = 0; i < edges.size(); i++) {
        std::vector<Edge>& other = nodes[edges[i].id].edges;
        other.erase(other.begin() + id);
    }
    nodes.erase(id);
};
void Graph::addEdge(int id1, int id2) {
    if (!nodes.count(id1) || !nodes.count(id2)) 
        return;

    std::vector<Edge>& edges1 = nodes[id1].edges;
    std::vector<Edge>& edges2 = nodes[id2].edges;

    int size1 = edges1.size();
    int size2 = edges2.size();
    for (int i = 0; i < size1; i++) {
        if (edges1[i].id == id2) return;
    }
    for (int i = 0; i < size2; i++) {
        if (edges2[i].id == id1) return;
    }
    edges1.push_back({id2, true});
    edges2.push_back({id1, false});
}
void Graph::removeEdge(int id1, int id2) {
    if (!nodes.count(id1) || !nodes.count(id2)) 
        return;

    std::vector<Edge>& edges1 = nodes[id1].edges;
    std::vector<Edge>& edges2 = nodes[id2].edges;

    int size1 = edges1.size();
    int size2 = edges2.size();
    for (int i = 0; i < size1; i++) {
        if (edges1[i].id == id2) {
            edges1.erase(edges1.begin() + i);
            break;
        }
    }
    for (int i = 0; i < size2; i++) {
        if (edges2[i].id == id1) {
            edges2.erase(edges2.begin() + i);
            break;
        }
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