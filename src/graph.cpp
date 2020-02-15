#include "graph.hpp"
#include <SFML/System/Vector2.hpp>
#include <cmath>

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

static float dot(sf::Vector2f a, sf::Vector2f b) {
    return a.x * b.x + a.y * b.y;
}
static bool isOnLine(sf::Vector2f a, sf::Vector2f b, sf::Vector2f p) {
    if (a.x <= b.x && (p.x < a.x || p.x > b.x)) return false;
    if (b.x <= a.x && (p.x < b.x || p.x > a.x)) return false;
    if (a.y <= b.y && (p.y < a.y || p.y > b.y)) return false;
    if (b.y <= a.y && (p.y < b.y || p.y > a.y)) return false;

    const float lenSqr = dot(b-a, b-a);
    if (lenSqr == 0) return true;
    
    const float t = dot(p-a, b-a) / lenSqr;
    const sf::Vector2f projection = a + t * (b - a);
    return dot(projection-p, projection-p) < EDGE_TOLERANCE*EDGE_TOLERANCE;
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

Edge Graph::findEdge(double x, double y) {
    for (auto i = edges.begin(); i != edges.end(); i++)
    {
        double x1 = nodes[i->id1].x;
        double y1 = nodes[i->id1].y;
        double x2 = nodes[i->id2].x;
        double y2 = nodes[i->id2].y;
        if (isOnLine(sf::Vector2f(x1, y1), sf::Vector2f(x2, y2), sf::Vector2f(x, y))) {
            return *i;
        }
    }
    return {0, 0};
}