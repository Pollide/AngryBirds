#include "InputManager.h"

void InputManager::InitializeButtons(sf::Font* font)
{

	Button::Transform transform;
	transform.font = font;

	float add = 80;

	CreateButton("ANGRY PIGS", transform, false, true);
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


void InputManager::UpdateButtons(const sf::RenderWindow* window, int* scene)
{
	int hold = 0;

	for (const auto& it : buttons) // Runs through all button objects
	{
		it.second->update(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y)); // Updates button state based on mouse position

		if (it.second->isPressed())
		{
			if (!holding)
			{
				holding = true;

				if (it.second->ButtonText == "SCENE ONE")
				{
					*scene = 1;
				}

				if (it.second->ButtonText == "SCENE TWO")
				{
					*scene = 2;
				}

				if (it.second->ButtonText == "SCENE THREE")
				{
					*scene = 3;
				}

				if (it.second->ButtonText == "OPTIONS")
				{
					*scene = 3;
				}

				if (it.second->ButtonText == "QUIT")
				{
					exit(0);
				}
			}
		}
		else
		{
			hold++;
		}
	}

	if (hold == buttons.size())
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

