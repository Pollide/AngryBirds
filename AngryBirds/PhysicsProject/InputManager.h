#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"
#include <sstream>

class InputManager
{
public:
	void InitializeButtons(sf::Font* font);
	void CreateButton(string _text, Button::Transform transform, bool _is_options = false, bool _is_title = false);
	void UpdateButtons(const sf::RenderWindow* window, int* sceneNumber);
	void RenderButtons(sf::RenderTarget* target);
	std::string CreateString(string attach, int value);
	bool holding;
	bool options;
	const int MaxVolume = 10; //keep above else it will be zero
	int MusicVolume = MaxVolume;
	int SoundVolume = MaxVolume;
	map<string, Button*> buttons;
};

