#include "Bird.h"

Bird::Bird() : Object(sf::Vector2f(450, 100), 0, b2BodyType::b2_dynamicBody, ReturnTextureName(), NULL, NULL)
{
	isBird = true;
}

sf::String Bird::ReturnTextureName()
{
	int randSprite = rand() % 6 + 1;
	//std::cout << randSprite;
	std::stringstream ss;
	ss << "Goons/Goon" << randSprite << ".png";

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