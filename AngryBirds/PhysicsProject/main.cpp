#include "Scene.h"
#include "Joint.h"
#include "InputManager.h"

InputManager inputManager;


int main()
{


	// Window
	sf::RenderWindow window(sf::VideoMode(960, 540), "Angry Birds!");
	window.setFramerateLimit(60);

	Scene* scene = new Scene();

	sf::Font font;
	font.loadFromFile("Resources/Rubik-Black.ttf");
	inputManager.InitializeButtons(&font);


	while (window.isOpen())
	{
		window.clear(sf::Color(97, 136, 235));


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (inputManager.scene > 0)
			{

				switch (event.type)
				{
				case sf::Event::MouseButtonPressed:
				{
					scene->MouseButtonPressed(window);
					break;
				}
				case sf::Event::MouseButtonReleased:
				{
					scene->MouseButtonReleased();
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

		if (inputManager.scene == 0)
		{
			inputManager.UpdateButtons(&window);
			inputManager.RenderButtons(&window);
		}
		else
		{
			scene->Create(inputManager.scene);
			scene->Update();
			scene->Render(window);
		}

		window.display();
	}

	return 0;
}