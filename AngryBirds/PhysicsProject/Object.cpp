#include "Object.h"

Object::Object(sf::Vector2f _position, float _scale, b2BodyType _bodyType, std::string _spriteName, b2World* _world)
{
	// Sprite Setup
	texture.loadFromFile("Resources/Sprites/" + _spriteName);
	sprite.setTexture(texture);
	float originX = (texture.getSize().x / 2);
	float originY = (texture.getSize().y / 2);
	sprite.setOrigin(originX, originY);

	// Box2D Setup
	bodyDef.position = b2Vec2(_position.x / _scale, _position.y / _scale);
	bodyDef.type = _bodyType;
	body = _world->CreateBody(&bodyDef);
	shape.SetAsBox(originX / _scale, originY / _scale);
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.8f; // Bounce
	fixtureDef.shape = &shape;
	body->CreateFixture(&fixtureDef);
}

void Object::Render(sf::RenderWindow& _window, float _scale)
{
	sprite.setPosition(body->GetPosition().x * _scale, body->GetPosition().y * _scale);
	sprite.setRotation(body->GetAngle() * 180 / b2_pi);
	_window.draw(sprite);
}