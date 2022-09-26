#pragma once

#include "Object.h"
#include "Catapult.h"
#include "Joint.h"

class Bird;

class Scene
{
public:
	Scene();

	void Render(sf::RenderWindow& _window);
	void Update();
	void Create(int scene);
	void MouseButtonPressed(sf::RenderWindow& _window);
	void MouseButtonReleased();
	void MouseMoved(sf::RenderWindow& _window);
	const double scale = 30.0;
	bool status = 0;
	std::vector<Bird*> birds;
	std::vector<Object*> objects;
	std::vector<std::unique_ptr<Object::FixtureUserData>> mFixtureUserData;

private:
	b2World* world;

	Catapult* catapult;
};