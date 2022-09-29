// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name :  
// Description:  
// Authors:

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
	void Create(int sceneRequested);
	void MouseButtonPressed(sf::RenderWindow& _window);
	void MouseButtonReleased(sf::RenderWindow& _window);
	void GetQueue(sf::RenderWindow& _window);
	void End();
	bool InView(sf::RenderWindow& _window, sf::Sprite sprite);
	Bird* NewBird(Bird* bird, sf::RenderWindow& _window);
	void AddQueue(int type);
	void MouseMoved(sf::RenderWindow& _window, b2World* _world);
	const double scale = 30.0;
	int menu = 0;
	//menu types
	//-1 - no menu
	//0 - main menu
	//1 - options menu
	//2 - game over menu

	int scene = 0;
	sf::Color Background;
	std::vector<Bird*> birds;
	std::vector<Object*> objects;
	std::vector<std::unique_ptr<Object::FixtureUserData>> mFixtureUserData;
	b2World* world;
private:
	
	Bird* launchedBird;
	Catapult* catapult;
};