#include <SFML/Graphics.hpp>
#include "gui.hpp"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "PEmbed");
    window.setFramerateLimit(60);

    Gui gui;

    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased:
                gui.handleMouseEvent(event);
                break;
            case sf::Event::Resized: {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            }
        }
        
        gui.update(window);

        window.clear(sf::Color::White);
        gui.draw(window);
        window.display();
    }
}