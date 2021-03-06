#pragma once

#include "graph.hpp"
#include <SFML/Graphics.hpp>

struct TextureBank {
    sf::Texture hand;
    sf::Texture plus;
    sf::Texture minus;
    sf::Texture draw;
    sf::Texture save;
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

    bool hasSavedPositions;
    SavedPositions savedPositions;
    double sliderPos;
    bool isGrabbingSlider;

    void invalidateSavedPositions();
public:
    Gui();
    void draw(sf::RenderWindow& window);
    void handleMouseEvent(sf::Event event);
    void update(sf::RenderWindow& window);
};