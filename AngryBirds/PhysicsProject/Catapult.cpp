#include "Catapult.h"
#include "Bird.h"
#include "box2d/box2d.h"

Catapult::Catapult(sf::Vector2f _position)
{
	// Sprite Setup
	texture.loadFromFile("Resources/Sprites/Catapult.png");
	sprite.setTexture(texture);
	float originX = (texture.getSize().x / 2);
	float originY = (texture.getSize().y / 2);
	sprite.setOrigin(originX, originY);

	sprite.setPosition(_position);

	firingOrigin = _position;
	firingOrigin.y -= texture.getSize().y / 2;
}

void Catapult::Render(sf::RenderWindow& _window)
{
	_window.draw(sprite);
}

void Catapult::LoadBird(Bird* _bird)
{
	loadedBird = _bird;
}

void Catapult::MoveBird(sf::RenderWindow& _window)
{
	if (loadedBird != nullptr)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);
		firingVector.x = mousePosition.x - firingOrigin.x;
		firingVector.y = mousePosition.y - firingOrigin.y;

		float length = sqrt((firingVector.x * firingVector.x) + (firingVector.y * firingVector.y)); // Magnitude
		if (length > 100.0f)
		{
			firingVector = (firingVector / length) * 100.0f;
		}

		loadedBird->sprite.setPosition(firingOrigin + firingVector);
	}
}

void Catapult::LaunchBird(float _scale, b2World& _world)
{
	if (loadedBird != nullptr)
	{
		loadedBird->Launch(_scale, loadedBird->sprite.getPosition(), _world);

		float launchStrength = 4.0f;
		b2Vec2 b2launchVector;
		b2launchVector.x = firingVector.x * -1.0f * launchStrength;
		b2launchVector.y = firingVector.y * -1.0f * launchStrength;

		loadedBird->body->ApplyLinearImpulseToCenter(b2launchVector, true);
		loadedBird = nullptr;
	}
}