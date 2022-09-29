#pragma once

#include "MouseJoint.h"

class Bird;
class b2World;

class Catapult
{
public:
	Catapult(sf::Vector2f _position, b2World* _world);

	void Render(sf::RenderWindow& _window);

	void LoadBird(Bird* _bird, sf::RenderWindow& _window, b2World* _world);
	void MoveBird(sf::RenderWindow& _window, b2World* _world);
	void LaunchBird(float _scale, b2World& _world);
	void ImpulseBody(b2Body* body, float launchStrength);
	void Update(float x, float y);
	Bird* loadedBird;
	sf::Vector2f firingVector;
	b2Body* bodyOne;
	b2Body* bodyTwo;
private:

	// Firing variables
	sf::Vector2f firingOrigin;

	b2BodyDef bodyDefOne;
	b2BodyDef bodyDefTwo;
	// SFML stuff
	sf::Sprite sprite;
	sf::Texture texture;

	MouseJoint mouseJointOne;
	MouseJoint mouseJointTwo;
};

