#include "Scene.h"
#include "Joint.h"
#include "InputManager.h"

InputManager inputManager;


int main()
{


	// Window
	sf::RenderWindow window(sf::VideoMode(960, 540), "Angry Pigs!");
	window.setFramerateLimit(60);

	Scene* scene = new Scene();

	sf::Font font;
	font.loadFromFile("Resources/Rubik-Black.ttf");
	inputManager.InitializeButtons(&font);


	while (window.isOpen())
	{
		window.clear(scene->Background);


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (scene->sceneNumber > 0)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
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
					scene->MouseMoved(window);
					break;
				}
				}
			}
		}

		if (scene->sceneNumber == 0)
		{
			inputManager.UpdateButtons(&window, &scene->sceneNumber);
			inputManager.RenderButtons(&window);
		}
		else
		{
			scene->Create(scene->sceneNumber);
			scene->Update();
			scene->Render(window);
		}

		window.display();
	}

	return 0;
}