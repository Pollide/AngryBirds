#include "Level.h"
#include <iostream>

int main()
{
    const double SCALE = 30.0;

    // Window
    sf::RenderWindow window(sf::VideoMode(960, 540), "SFML and box2D works!");
    window.setFramerateLimit(60);

    Level* level = new Level(SCALE);

    while (window.isOpen())
    {
        window.clear(sf::Color(97, 136, 235));

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            switch (event.type)
            {
            case sf::Event::MouseButtonPressed:
            {
                level->MouseButtonPressed(window);
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                level->MouseButtonReleased();
                break;
            }
            case sf::Event::MouseMoved:
            {
                level->MouseMoved(window);
                break;
            }
            }
        }

        level->Update();
        level->Render(window, SCALE);
        window.display();
    }

    return 0;
}