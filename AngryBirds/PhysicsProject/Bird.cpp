#include "Bird.h"

Bird::Bird(int _type, bool _waiting) : Object(sf::Vector2f(450, 100), 0, b2BodyType::b2_dynamicBody, ReturnTextureName(_type), NULL, NULL, _type)
{
	waiting = _waiting;
}

sf::String Bird::ReturnTextureName(int _type)
{
	//int randSprite = rand() % 3 + 1;
	//std::cout << randSprite;
	std::stringstream ss;
	ss << "Characters/AngryPig" << _type << ".png";

	return ss.str();
}

void Bird::Render(sf::RenderWindow& _window, float _scale)
{
	if (body != nullptr)
	{
		sprite.setPosition(body->GetPosition().x * _scale, body->GetPosition().y * _scale);
		sprite.setRotation(body->GetAngle() * 180 / b2_pi);
	}

	_window.draw(sprite);
}