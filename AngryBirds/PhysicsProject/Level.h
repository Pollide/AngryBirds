#pragma once

#include "Object.h"
#include "Catapult.h"
#include "Joint.h"

class Bird;

class Level
{
public:
	Level(float _scale);

	void Render(sf::RenderWindow& _window, float _scale);
	void Update();

	void MouseButtonPressed(sf::RenderWindow& _window);
	void MouseButtonReleased();
	void MouseMoved(sf::RenderWindow& _window);

	std::vector<Bird*> birds;
	std::vector<Object*> objects;
private:
	b2World* world;

	Catapult* catapult;
};