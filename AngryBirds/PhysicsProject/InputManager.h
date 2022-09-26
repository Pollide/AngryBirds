#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"

class InputManager
{
public:
	void InitializeButtons(sf::Font* font);
	void UpdateButtons(const sf::RenderWindow* window);
	void RenderButtons(sf::RenderTarget* target);
	bool holding;
	int scene = 0;
	map<string, Button*> buttons;
};

