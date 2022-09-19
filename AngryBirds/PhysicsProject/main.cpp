#include "Level.h"
#include "Joint.h"
#include "InputManager.h"
#include <iostream>

InputManager inputManager;

int main()
{
	const double SCALE = 30.0;

	// Window
	sf::RenderWindow window(sf::VideoMode(960, 540), "Angry Birds!");
	window.setFramerateLimit(60);

	Level* level = new Level(SCALE);

	sf::Font font;
	font.loadFromFile("Resources/Rubik-Black.ttf");
	inputManager.initialize_buttons(&font);


	while (window.isOpen())
	{
		window.clear(sf::Color(97, 136, 235));


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (!inputManager.paused)
			{

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
		}

		if (inputManager.paused)
		{
			inputManager.update_buttons(&window);
			inputManager.render_buttons(&window);
		}
		else
		{

			level->Update();
			level->Render(window, SCALE);
		}

		window.display();
	}

	return 0;
}