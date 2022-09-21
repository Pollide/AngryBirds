#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include "Object.h"

class Bird : public Object
{
public:
	Bird();

	sf::String ReturnTextureName();

	void Render(sf::RenderWindow& _window, float _scale);
};