#include "gui.hpp"
#include <cmath>
#include <iostream>

Gui::Gui() : grabbedNode(0) {
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
    
    if (realLen > 0) {
        sf::RectangleShape edge(sf::Vector2f(realLen, EDGE_WIDTH));
        edge.setFillColor(sf::Color::Black);
        edge.setPosition(realStart);
        float angle = atan2(dist.y, dist.x) * 180/PI;
        edge.setRotation(angle);
        window.draw(edge);
    }
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

void Gui::handleMouseEvent(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed && 
            event.mouseButton.button == sf::Mouse::Left) {
        int id = graph.findNode(event.mouseButton.x, event.mouseButton.y);
        if (id) {
            grabbedNode = id;
        };
    } else if (event.type == sf::Event::MouseButtonReleased &&
            event.mouseButton.button == sf::Mouse::Left) {
        grabbedNode = 0;
    }
}

void Gui::update(sf::RenderWindow& window) {
    if (grabbedNode) {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        graph.moveNode(grabbedNode, pos.x, pos.y);
    }
}