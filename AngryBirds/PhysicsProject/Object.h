#pragma once

#include "SFML/Graphics.hpp"
#include "Listener.h"
#include <sstream>

class Object
{


public:
	Listener listener;
	Object(sf::Vector2f _position, float _scale, b2BodyType _bodyType, std::string _spriteName, b2World* _world, std::vector<std::unique_ptr<MyFixtureUserDataType>>* mFixtureUserData);
	void CreatePhysics(sf::Vector2f _position, float _scale, b2BodyType _bodyType, b2World* _world);
	void Render(sf::RenderWindow& _window, float _scale);
	void Poof();
	void LoadTexture(std::string _spriteName);

	bool isBird;
	//private:
		// Box 2D Stuff
	b2BodyDef bodyDef;
	b2Body* body;
	b2PolygonShape shape;
	b2FixtureDef fixtureDef;

	// SFML Stuff
	sf::Sprite sprite;
	sf::Texture texture;



};