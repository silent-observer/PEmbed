#pragma once

#include "graph.hpp"
#include <SFML/Graphics.hpp>

struct TextureBank {
    sf::Texture hand;
    sf::Texture plus;
    sf::Texture minus;
    sf::Texture draw;
    TextureBank();
};

enum Tool {
    Pan,
    AddNode,
    RemoveNodeOrEdge,
    AddEdge
};

class Gui {
private:
    Graph graph;
    int grabbedNode;
    TextureBank textures;
    Tool currentTool;
    int edgeStartNode;
public:
    Gui();
    void draw(sf::RenderWindow& window);
    void handleMouseEvent(sf::Event event);
    void update(sf::RenderWindow& window);
};