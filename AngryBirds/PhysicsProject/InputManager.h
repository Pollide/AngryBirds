#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"

class InputManager
{
public:
	void InitializeButtons(sf::Font* font);
	void CreateButton(string _text, Button::Transform transform, bool _is_options = false, bool _is_title = false);
	void UpdateButtons(const sf::RenderWindow* window, int* sceneNumber);
	void RenderButtons(sf::RenderTarget* target);
	bool holding;
	map<string, Button*> buttons;
};

