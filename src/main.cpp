#include <SFML/Graphics.hpp>
#include "gui.hpp"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "PEmbed");

    Gui gui;

    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        gui.draw(window);
        window.display();
    }
}