#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Bird;
class b2World;

class Catapult
{
public:
	Catapult(sf::Vector2f _position);

	void Render(sf::RenderWindow& _window);

	void LoadBird(Bird* _bird);
	void MoveBird(sf::RenderWindow& _window);
	void ConvertFiring();
	void LaunchBird(float _scale, b2World& _world);
	void ImpulseBody(b2Body* body, float launchStrength);
	Bird* loadedBird;
	sf::Vector2f firingVector;
private:

	// Firing variables
	sf::Vector2f firingOrigin;

	// SFML stuff
	sf::Sprite sprite;
	sf::Texture texture;
};

