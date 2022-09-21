#include "InputManager.h"

void InputManager::initialize_buttons(sf::Font* font)
{
	buttons["Angry Birds"] = new Button(420, 130, 150, 50, font, "ANGRY BIRDS", sf::Color::White, sf::Color{ 0, 55, 55, 255 }, sf::Color{ 0, 55, 55, 125 }, false, true);
	buttons["Play"] = new Button(420, 230, 150, 50, font, "PLAY", sf::Color::White, sf::Color{ 55, 55, 55, 255 }, sf::Color{ 55, 55, 55, 125 });
	buttons["Options"] = new Button(420, 330, 150, 50, font, "OPTIONS", sf::Color::White, sf::Color{ 55, 55, 55, 255 }, sf::Color{ 55, 55, 55, 125 });
	buttons["Quit"] = new Button(420, 430, 150, 50, font, "QUIT", sf::Color::White, sf::Color{ 55, 55, 55, 255 }, sf::Color{ 55, 55, 55, 125 });
}

void InputManager::update_buttons(const sf::RenderWindow* window)
{
	for (const auto& it : buttons) // Runs through all button objects
	{
		it.second->update(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y)); // Updates button state based on mouse position
	//else
	//	it.second->buttonState = IDLE;
	}

	// Changes AI state and "Current Behaviour" text if one of the buttons is pressed
	if (buttons["Play"]->isPressed())
	{
		if (!holding)
		{
			//cout << "Play button works";
			paused = false;
			holding = true;
		}
	}
	else if (buttons["Options"]->isPressed())
	{
		if (!holding)
		{
			//cout << "Option button works";
			holding = true;
		}
	}
	else if (buttons["Quit"]->isPressed())
	{
		if (!holding)
		{
			//cout << "Quit button works";
			exit(0);
			holding = true;
		}
	}
	else
	{
		holding = false;
	}
}

void InputManager::render_buttons(sf::RenderTarget* target)
{
	for (auto& it : buttons) // For all buttons in the map
	{
		it.second->render(target);
	}
}

