#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Bird
{
public:
	Bird();

	void Render(sf::RenderWindow& _window, float _scale);
	void Launch(float _scale, sf::Vector2f _position, b2World& _world);

	sf::Sprite sprite;
	b2Body* body;
private:
	// Box 2D Stuff
	b2BodyDef bodyDef;
	b2CircleShape shape;
	b2FixtureDef fixtureDef;

	// SFML Stuff
	sf::Texture texture;
};