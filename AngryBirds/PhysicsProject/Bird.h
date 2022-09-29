#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include "Object.h"

class Bird : public Object
{
public:
	Bird(int _type, b2World* _world, std::vector<std::unique_ptr<FixtureUserData>>* mFixtureUserData, bool _waiting = false);

	sf::String ReturnTextureName(int _type);

	void Render(sf::RenderWindow& _window, float _scale);

	bool waiting;
};