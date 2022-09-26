#include "InputManager.h"

void InputManager::InitializeButtons(sf::Font* font)
{

	Button::Transform transform;
	transform.font = font;

	float add = 80;

	CreateButton("ANGRY BIRDS", transform, false, true);
	transform.y += add;
	CreateButton("SCENE ONE", transform);
	transform.y += add / 1.3f;
	CreateButton("SCENE TWO", transform);
	transform.y += add / 1.3f;
	CreateButton("SCENE THREE", transform);
	transform.y += add * 1.5f;
	CreateButton("OPTIONS", transform);
	transform.y += add;
	CreateButton("QUIT", transform);
}

void InputManager::CreateButton(string _text, Button::Transform transform, bool _is_options, bool _is_title)
{
	buttons[_text] = new Button(transform, _text, sf::Color::White, sf::Color{ 55, 55, 55, 255 }, sf::Color{ 55, 55, 55, 125 }, _is_options, _is_title);
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
	if (buttons["SCENE ONE"]->isPressed())
	{
		if (!holding)
		{
			//cout << "Play button works";
			scene = 1;
			holding = true;
		}
	}
	if (buttons["SCENE TWO"]->isPressed())
	{
		if (!holding)
		{
			//cout << "Play button works";
			scene = 2;
			holding = true;
		}
	}
	if (buttons["SCENE THREE"]->isPressed())
	{
		if (!holding)
		{
			//cout << "Play button works";
			scene = 3;
			holding = true;
		}
	}
	else if (buttons["OPTIONS"]->isPressed())
	{
		if (!holding)
		{
			//cout << "Option button works";
			holding = true;
		}
	}
	else if (buttons["QUIT"]->isPressed())
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

