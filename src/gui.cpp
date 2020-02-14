#include "gui.hpp"
#include <cmath>
#include <iostream>

Gui::Gui() {
    graph.addNode(100, 100);
    graph.addNode(200, 100);
    graph.addNode(100, 200);
    graph.addNode(200, 200);

    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 1);
}

static void drawEdge(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end) {
    const float EDGE_OFFSET = 3;
    const float EDGE_WIDTH = 2;
    const double PI = 3.1415926;

    sf::Vector2f dist = end - start;
    float len = sqrt(dist.x * dist.x + dist.y * dist.y);
    sf::Vector2f dir = dist / len;
    
    sf::Vector2f realStart = start + (float)(NODE_RADIUS + EDGE_OFFSET) * dir;
    float realLen = len - 2 * (NODE_RADIUS + EDGE_OFFSET);
    
    sf::RectangleShape edge(sf::Vector2f(realLen, EDGE_WIDTH));
    edge.setFillColor(sf::Color::Black);
    edge.setPosition(realStart);
    float angle = atan2(dist.y, dist.x) * 180/PI;
    edge.setRotation(angle);
    window.draw(edge);
}

void Gui::draw(sf::RenderWindow& window) {
    sf::CircleShape nodeShape(NODE_RADIUS);
    nodeShape.setFillColor(sf::Color::Black);
    nodeShape.setOrigin(NODE_RADIUS, NODE_RADIUS);

    for (auto n = graph.nodes.begin(); n != graph.nodes.end(); n++) {
        sf::Vector2f nodePos(n->second.x, n->second.y);
        for (auto e = n->second.edges.begin(); e != n->second.edges.end(); e++) {
            if (!e->isFirst) continue;
            double x1 = graph.nodes[e->id].x;
            double y1 = graph.nodes[e->id].y;
            sf::Vector2f endPos(x1, y1);
            drawEdge(window, nodePos, endPos);
        }
        nodeShape.setPosition(nodePos);
        window.draw(nodeShape);
    }
}