// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name :  
// Description:  
// Authors:

#include "InputManager.h"

void InputManager::InitializeButtons(sf::Font* font)
{

	Button::Transform transform;
	transform.font = font;

	float add = 80;

	CreateButton("ANGRY PIGS", transform, 0, true);
	CreateButton("OPTIONS MENU", transform, 1, true);
	CreateButton("GAME OVER", transform, 2, true);
	CreateButton("SUCCESS!", transform, 3, true);
	CreateButton("ALL LEVELS COMPLETE!", transform, 4, true);

	transform.y += add;

	CreateButton("TRY AGAIN", transform, 2);
	CreateButton("MAIN MENU", transform, 4);

	Button::Transform newTransform = transform;
	newTransform.x -= 85;
	CreateButton("REPLAY", newTransform, 3);

	CreateButton("SCENE ONE", transform);
	CreateButton("MUSIC", transform, 1);
	transform.y += add / 1.3f;

	newTransform.x += 85 * 2;
	CreateButton("NEXT", newTransform, 3);

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

void InputManager::InitializeMusic()
{
	music.openFromFile("Resources/Sounds/AngryPigsMusic.wav");
	music.play();
	music.setLoop(true);

	//sound.openFromFile("Resources/Sounds/AngryPigsMusic.wav");
	//sound.setVolume(50.0f);
	//sound.play();
	//sound.setLoop(true);
}

void InputManager::CreateButton(string _text, Button::Transform transform, int _status, bool _is_title)
{
	buttons[_text] = new Button(transform, _text, sf::Color::White, sf::Color{ 55, 55, 55, 255 }, sf::Color{ 55, 55, 55, 125 }, _status, _is_title);
}

std::string InputManager::CreateString(string attach, int value)
{
	std::stringstream ss;
	ss << attach << value;

	return ss.str();
}

void InputManager::UpdateButtons(const sf::RenderWindow* window, Scene* scene)
{
	int unpressed = 0;

	for (const auto& it : buttons) // Runs through all button objects
	{
		if (it.second->menu == scene->menu)
		{
			it.second->update(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y)); // Updates button state based on mouse position

			if (it.second->isPressed())
			{
				if (!holding)
				{
					holding = true;

					if (it.second->ButtonText == "SCENE ONE")
					{
						scene->scene = 1;
					}

					if (it.second->ButtonText == "SCENE TWO")
					{
						scene->scene = 2;
					}

					if (it.second->ButtonText == "SCENE THREE")
					{
						scene->scene = 3;
					}

					if (it.second->ButtonText == "MAIN MENU")
					{
						scene->scene = 0;
						scene->End();
					}

					if (it.second->ButtonText == "OPTIONS")
					{
						scene->menu = 1;
					}

					if (it.second->ButtonText == "TRY AGAIN" || it.second->ButtonText == "REPLAY")
					{
						scene->End();
					}

					if (it.second->ButtonText == "NEXT")
					{
						scene->End();
						scene->scene += 1;
					}


					if (it.second->ButtonText == "MUSIC")
					{
						MusicVolume++;

						if (MusicVolume > MaxVolume)
							MusicVolume = 0;

						music.setVolume(MusicVolume * 10);

						cout << MusicVolume;
						cout << music.getVolume();
					}

					if (it.second->ButtonText == "BACK")
					{
						scene->menu = 0;
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

void InputManager::RenderButtons(sf::RenderTarget* target, int* menu)
{
	//std::cout << *menu << "|";

	for (auto& it : buttons) // For all buttons in the map
	{
		//std::cout << &it.second->menu << "==" << menu << "|";

		if (it.second->menu == *menu)
			it.second->render(target);
	}
}