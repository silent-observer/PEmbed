#pragma once

#include "graph.hpp"
#include <SFML/Graphics.hpp>

class Gui {
private:
    Graph graph;
    int grabbedNode;
public:
    Gui();
    void draw(sf::RenderWindow& window);
    void handleMouseEvent(sf::Event event);
    void update(sf::RenderWindow& window);
};