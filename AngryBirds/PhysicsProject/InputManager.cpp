#include "InputManager.h"

void InputManager::InitializeButtons(sf::Font* font)
{

	Button::Transform transform;
	transform.font = font;

	float add = 80;

	CreateButton("ANGRY PIGS", transform, false, true);
	CreateButton("OPTIONS MENU", transform, true, true);
	transform.y += add;
	CreateButton("SCENE ONE", transform);
	CreateButton("MUSIC", transform, true);
	transform.y += add / 1.3f;
	CreateButton("SOUND", transform, true);
	CreateButton("SCENE TWO", transform);
	transform.y += add / 1.3f;

	CreateButton("SCENE THREE", transform);


	transform.y += add * 0.75f;

	transform.characterSize = 10;
	CreateButton("How to play:\nHold the mouse and drag around to aim.\nLet go to slingshot a pig, aim for the enemy birds.\nOnce all are hit, you win\n You lose if you run out of pigs.", transform, true, true);
	transform.characterSize = 22;

	transform.y += add * 0.5f;

	CreateButton("OPTIONS", transform);
	transform.y += add * 1.3f;
	CreateButton("BACK", transform, true);
	CreateButton("QUIT", transform);
}

void InputManager::CreateButton(string _text, Button::Transform transform, bool _is_options, bool _is_title)
{
	buttons[_text] = new Button(transform, _text, sf::Color::White, sf::Color{ 55, 55, 55, 255 }, sf::Color{ 55, 55, 55, 125 }, _is_options, _is_title);
}

std::string InputManager::CreateString(string attach, int value)
{
	std::stringstream ss;
	ss << attach << value;

	return ss.str();
}

void InputManager::UpdateButtons(const sf::RenderWindow* window, int* scene)
{
	int unpressed = 0;

	for (const auto& it : buttons) // Runs through all button objects
	{
		if (it.second->is_options == options)
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
						options = true;
					}

					if (it.second->ButtonText == "SOUND")
					{
						SoundVolume++;

						if (SoundVolume > MaxVolume)
							SoundVolume = 0;
					}

					if (it.second->ButtonText == "MUSIC")
					{
						MusicVolume++;

						if (MusicVolume > MaxVolume)
							MusicVolume = 0;
					}

					if (it.second->ButtonText == "SOUND")
					{
						SoundVolume++;

						if (SoundVolume > MaxVolume)
							SoundVolume = 0;
					}

					if (it.second->ButtonText == "BACK")
					{
						options = false;
					}

					if (it.second->ButtonText == "QUIT")
					{
						exit(0);
					}
				}
			}
			else
			{
				unpressed++;
			}

			if (it.second->ButtonText == "MUSIC")
				it.second->set_text(CreateString("MUSIC: ", MusicVolume));

			if (it.second->ButtonText == "SOUND")
				it.second->set_text(CreateString("SOUND: ", SoundVolume));
		}
		else
		{
			unpressed++;
		}
	}

	if (unpressed == buttons.size())
	{
		holding = false;
	}
}

void InputManager::RenderButtons(sf::RenderTarget* target)
{
	for (auto& it : buttons) // For all buttons in the map
	{
		if (it.second->is_options == options)
			it.second->render(target);
	}
}

