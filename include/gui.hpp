#pragma once

#include "graph.hpp"
#include <SFML/Graphics.hpp>

class Gui {
private:
    Graph graph;
public:

    Gui();
    void draw(sf::RenderWindow& window);
    void handleClick(int x, int y);
};