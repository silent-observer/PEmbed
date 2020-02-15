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

class Gui {
private:
    Graph graph;
    int grabbedNode;
    TextureBank textures;
public:
    Gui();
    void draw(sf::RenderWindow& window);
    void handleMouseEvent(sf::Event event);
    void update(sf::RenderWindow& window);
};