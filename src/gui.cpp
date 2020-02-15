#include "gui.hpp"
#include <cmath>
#include <iostream>
#include <windows.h>

TextureBank::TextureBank() {
    bool b1 = hand.loadFromFile("resources/hand.png");
    bool b2 = plus.loadFromFile("resources/plus.png");
    bool b3 = minus.loadFromFile("resources/minus.png");
    bool b4 = draw.loadFromFile("resources/draw.png");
    if (!b1 || !b2 || !b3 || !b4) {
        MessageBoxA(NULL, "Couldn't load resources!", "Error", MB_ICONERROR | MB_OK);
        exit(1);
    }
}

Gui::Gui() : grabbedNode(0), currentTool(Tool::Pan) {
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

static void drawGraph(sf::RenderWindow& window, Graph& graph) {
    sf::CircleShape nodeShape(NODE_RADIUS);
    nodeShape.setFillColor(sf::Color::Black);
    nodeShape.setOrigin(NODE_RADIUS, NODE_RADIUS);

    for (auto n = graph.nodes.begin(); n != graph.nodes.end(); n++) {
        sf::Vector2f nodePos(n->second.x, n->second.y);
        nodeShape.setPosition(nodePos);
        window.draw(nodeShape);
    }

    for (auto e = graph.edges.begin(); e != graph.edges.end(); e++) {
        double x1 = graph.nodes[e->id1].x;
        double y1 = graph.nodes[e->id1].y;
        double x2 = graph.nodes[e->id2].x;
        double y2 = graph.nodes[e->id2].y;
        sf::Vector2f startPos(x1, y1);
        sf::Vector2f endPos(x2, y2);
        drawEdge(window, startPos, endPos);
    }
}
const float BUTTON_SIZE = 30;
const float BUTTON_OFFSET = 30;

static void drawButtons(sf::RenderWindow& window, TextureBank& textures, Tool currentTool) {
    sf::RectangleShape rect(sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE));
    rect.setOrigin(BUTTON_SIZE/2, BUTTON_SIZE/2);
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(2);
    for (int i = 0; i < 4; i++) {
        rect.setPosition(sf::Vector2f(BUTTON_OFFSET + i*BUTTON_SIZE, BUTTON_OFFSET));
        window.draw(rect);
    }

    rect.setPosition(sf::Vector2f(BUTTON_OFFSET + (int)currentTool*BUTTON_SIZE, BUTTON_OFFSET));
    rect.setOutlineColor(sf::Color::Red);
    window.draw(rect);

    sf::Sprite sprite;
    sprite.setOrigin(13, 12);
    
    for (int i = 0; i < 4; i++) {
        switch (i) {
            case 0: sprite.setTexture(textures.hand); break;
            case 1: sprite.setTexture(textures.plus); break;
            case 2: sprite.setTexture(textures.minus); break;
            case 3: sprite.setTexture(textures.draw); break;
        }
        sprite.setPosition(sf::Vector2f(BUTTON_OFFSET + i*BUTTON_SIZE, BUTTON_OFFSET));
        window.draw(sprite);
    }
}

const sf::IntRect buttonsRect(BUTTON_OFFSET - 0.5*BUTTON_SIZE,
                              BUTTON_OFFSET - 0.5*BUTTON_SIZE,
                              4*BUTTON_SIZE,
                              BUTTON_SIZE);

void Gui::draw(sf::RenderWindow& window) {
    drawGraph(window, graph);
    drawButtons(window, textures, currentTool);
}


void Gui::handleMouseEvent(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed && 
            event.mouseButton.button == sf::Mouse::Left) {
        if (buttonsRect.contains(event.mouseButton.x, event.mouseButton.y)) {
            double x = (event.mouseButton.x - BUTTON_OFFSET)/BUTTON_SIZE;
            int i = round(x);
            currentTool = (Tool)i;
        }
        else switch(currentTool) {
            case Tool::Pan: {
                int id = graph.findNode(event.mouseButton.x, event.mouseButton.y);
                if (id) {
                    grabbedNode = id;
                }
                break;
            }
            case Tool::AddNode:
                graph.addNode(event.mouseButton.x, event.mouseButton.y);
                break;
            case Tool::RemoveNodeOrEdge: {
                int id = graph.findNode(event.mouseButton.x, event.mouseButton.y);
                if (id) {
                    graph.removeNode(id);
                }
                break;
            }
        }
    } else if (event.type == sf::Event::MouseButtonReleased &&
            event.mouseButton.button == sf::Mouse::Left) {
        if (currentTool == Tool::Pan)
            grabbedNode = 0;
    }
}

void Gui::update(sf::RenderWindow& window) {
    if (grabbedNode) {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        sf::IntRect windowRect(sf::Vector2i(0, 0), (sf::Vector2i)window.getSize());
        if (buttonsRect.contains(pos) || !windowRect.contains(pos))
            grabbedNode = 0;
        else
            graph.moveNode(grabbedNode, pos.x, pos.y);
    }
}