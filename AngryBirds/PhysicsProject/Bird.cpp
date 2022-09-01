#include "Bird.h"

Bird::Bird()
{
	int randSprite = rand() % 6;

	switch (randSprite)
	{
	case 0:
		texture.loadFromFile("Resources/Sprites/Goon1.png");
		break;
	case 1:
		texture.loadFromFile("Resources/Sprites/Goon2.png");
		break;
	case 2:
		texture.loadFromFile("Resources/Sprites/Goon3.png");
		break;
	case 3:
		texture.loadFromFile("Resources/Sprites/Goon4.png");
		break;
	case 4:
		texture.loadFromFile("Resources/Sprites/Goon5.png");
		break;
	case 5:
		texture.loadFromFile("Resources/Sprites/Goon6.png");
		break;
	}

	// Sprite Setup
	sprite.setTexture(texture);
	float originX = (texture.getSize().x / 2);
	float originY = (texture.getSize().y / 2);
	sprite.setOrigin(originX, originY);
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

void Bird::Launch(float _scale, sf::Vector2f _position, b2World& _world)
{
	// Box2D Setup
	bodyDef.position = b2Vec2(_position.x / _scale, _position.y / _scale);
	bodyDef.type = b2_dynamicBody;
	body = _world.CreateBody(&bodyDef);
	//float originX = (texture.getSize().x / 2);
	shape.m_radius = (texture.getSize().x / 2) / _scale;
	fixtureDef.density = 5.0f;
	fixtureDef.shape = &shape;
	body->CreateFixture(&fixtureDef);
}