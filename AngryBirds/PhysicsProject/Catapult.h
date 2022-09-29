#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include "MouseJoint.h"

class Bird;
class b2World;

class Catapult
{
public:
	Catapult(sf::Vector2f _position);

	void Render(sf::RenderWindow& _window);

	void LoadBird(Bird* _bird, sf::RenderWindow& _window, b2World* _world);
	void MoveBird(sf::RenderWindow& _window, b2World* _world);
	void LaunchBird(float _scale, b2World& _world);
	void ImpulseBody(b2Body* body, float launchStrength);
	void Update(float x, float y);
	Bird* loadedBird;

private:

	// Firing variables
	sf::Vector2f firingOrigin;
	sf::Vector2f firingVector;

	// SFML stuff
	sf::Sprite sprite;
	sf::Texture texture;

	MouseJoint* mouseJointObject;
};

