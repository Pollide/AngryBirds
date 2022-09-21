#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"

class InputManager
{
public:
	void initialize_buttons(sf::Font* font);
	void update_buttons(const sf::RenderWindow* window);
	void render_buttons(sf::RenderTarget* target);
	bool holding;
	bool paused = true;
	map<string, Button*> buttons;
};

