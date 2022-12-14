#include "Scene.h"
#include "Joint.h"
#include "InputManager.h"

InputManager inputManager;

int main()
{
	// Window parameters
	sf::RenderWindow window(sf::VideoMode(1260, 540), "Angry Pigs", sf::Style::None | sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);

	// UI parameters
	Scene* scene = new Scene();
	sf::Font font;
	font.loadFromFile("Resources/Rubik-Black.ttf");
	inputManager.InitializeButtons(&font);
	inputManager.InitializeMusic();

	// Main loop
	while (window.isOpen())
	{
		window.clear(scene->Background);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (scene->scene > 0)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					scene->scene = 0;
					scene->End();
				}

				switch (event.type)
				{
					case sf::Event::MouseButtonPressed:
					{
						scene->MouseButtonPressed(window);
						break;
					}
					case sf::Event::MouseButtonReleased:
					{
						scene->MouseButtonReleased(window);
						break;
					}
					case sf::Event::MouseMoved:
					{
						scene->MouseMoved(window, scene->world);
						break;
					}
				}
			}
		}

		inputManager.UpdateButtons(&window, scene);
		inputManager.RenderButtons(&window, &scene->menu);

		if (scene->scene > 0)
		{
			scene->Create(scene->scene);

			scene->Update();
			scene->Render(window);
		}

		window.display();
	}

	return 0;
}