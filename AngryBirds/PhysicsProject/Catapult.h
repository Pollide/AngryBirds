#pragma once

#include "SFML/Graphics.hpp"

class Bird;
class b2World;

class Catapult
{
public:
	Catapult(sf::Vector2f _position);

	void Render(sf::RenderWindow& _window);

	void LoadBird(Bird* _bird);
	void MoveBird(sf::RenderWindow& _window);
	void LaunchBird(float _scale, b2World& _world);

private:
	Bird* loadedBird;

	// Firing variables
	sf::Vector2f firingOrigin;
	sf::Vector2f firingVector;

	// SFML stuff
	sf::Sprite sprite;
	sf::Texture texture;
};

