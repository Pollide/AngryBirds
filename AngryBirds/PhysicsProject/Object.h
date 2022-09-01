#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Object
{
public:
	Object(sf::Vector2f _position, float _scale, b2BodyType _bodyType, std::string _spriteName, b2World* _world);

	void Render(sf::RenderWindow& _window, float _scale);

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