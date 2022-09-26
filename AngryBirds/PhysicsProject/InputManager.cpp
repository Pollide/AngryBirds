#include "InputManager.h"

void InputManager::InitializeButtons(sf::Font* font)
{
	int y = 50;
	float add = 80;
	buttons["Angry Birds"] = new Button(420, y, 160, 50, font, "ANGRY BIRDS", sf::Color::White, sf::Color{ 0, 55, 55, 255 }, sf::Color{ 0, 55, 55, 125 }, false, true);
	y += add;
	buttons["Scene One"] = new Button(420, y, 160, 50, font, "LEVEL ONE", sf::Color::White, sf::Color{ 55, 55, 55, 255 }, sf::Color{ 55, 55, 55, 125 });
	y += add / 1.3f;
	buttons["Scene Two"] = new Button(420, y, 160, 50, font, "LEVEL TWO", sf::Color::White, sf::Color{ 55, 55, 55, 255 }, sf::Color{ 55, 55, 55, 125 });
	y += add / 1.3f;
	buttons["Scene Three"] = new Button(420, y, 160, 50, font, "LEVEL THREE", sf::Color::White, sf::Color{ 55, 55, 55, 255 }, sf::Color{ 55, 55, 55, 125 });
	y += add * 1.5f;
	buttons["Options"] = new Button(420, y, 160, 50, font, "OPTIONS", sf::Color::White, sf::Color{ 55, 55, 55, 255 }, sf::Color{ 55, 55, 55, 125 });
	y += add;
	buttons["Quit"] = new Button(420, y, 160, 50, font, "QUIT", sf::Color::White, sf::Color{ 55, 55, 55, 255 }, sf::Color{ 55, 55, 55, 125 });
}


void InputManager::UpdateButtons(const sf::RenderWindow* window)
{
	for (const auto& it : buttons) // Runs through all button objects
	{
		it.second->update(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y)); // Updates button state based on mouse position
	//else
	//	it.second->buttonState = IDLE;
	}

	// Changes AI state and "Current Behaviour" text if one of the buttons is pressed
	if (buttons["Scene One"]->isPressed())
	{
		if (!holding)
		{
			//cout << "Play button works";
			scene = 1;
			holding = true;
		}
	}
	if (buttons["Scene Two"]->isPressed())
	{
		if (!holding)
		{
			//cout << "Play button works";
			scene = 2;
			holding = true;
		}
	}
	if (buttons["Scene Three"]->isPressed())
	{
		if (!holding)
		{
			//cout << "Play button works";
			scene = 3;
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

void InputManager::RenderButtons(sf::RenderTarget* target)
{
	for (auto& it : buttons) // For all buttons in the map
	{
		it.second->render(target);
	}
}

