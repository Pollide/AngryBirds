#pragma once

#include "Object.h"
#include "Catapult.h"
#include "Joint.h"

class Bird;

class Scene
{
public:
	Scene();
	void Initialise();
	void Render(sf::RenderWindow& _window);
	void Update();
	void Create(int scene);
	void MouseButtonPressed(sf::RenderWindow& _window);
	void MouseButtonReleased(sf::RenderWindow& _window);
	void GetQueue(sf::RenderWindow& _window);
	void End();
	Bird* NewBird(Bird* bird, sf::RenderWindow& _window);
	void AddQueue(int type);
	void MouseMoved(sf::RenderWindow& _window);
	const double scale = 30.0;
	bool status = 0;
	int sceneNumber = 0;
	sf::Color Background;
	std::vector<Bird*> birds;
	std::vector<Object*> objects;
	std::vector<std::unique_ptr<Object::FixtureUserData>> mFixtureUserData;

private:
	b2World* world;
	Bird* launchedBird;
	Catapult* catapult;
};