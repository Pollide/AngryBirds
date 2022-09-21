#include "Object.h"
#include <iostream>


Object::Object(sf::Vector2f _position, float _scale, b2BodyType _bodyType, std::string _spriteName, b2World* _world)
{
	// Sprite Setup
	texture.loadFromFile("Resources/Sprites/" + _spriteName);
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	spriteName = _spriteName;

	if (_world != NULL) //if it isnt NULL, then this is an object, else it would be a bird
	{
		CreatePhysics(_position, _scale, _bodyType, _world);
	}
}

void Object::CreatePhysics(sf::Vector2f _position, float _scale, b2BodyType _bodyType, b2World* _world)
{

	shape.SetAsBox(sprite.getOrigin().x / _scale, sprite.getOrigin().y / _scale);
	fixtureDef.density = 1.0f;
	fixtureDef.shape = &shape;

	if (isBird)
	{
		//circleShape.m_radius = (texture.getSize().x / 2) / _scale;
		fixtureDef.density = 5.0f;
	}
	else
	{
		fixtureDef.restitution = 0.8f; // Bounce
	}

	bodyDef.position = b2Vec2(_position.x / _scale, _position.y / _scale);
	bodyDef.type = _bodyType;
	//bodyDef.userData = sprite;//needs to be before CreateBody()
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	_world->SetContactListener(&listener);
	body = _world->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);

}





void Object::Render(sf::RenderWindow& _window, float _scale)
{
	sprite.setPosition(body->GetPosition().x * _scale, body->GetPosition().y * _scale);

	//b2Vec2 vel = body->GetLinearVelocity();
	//float angle = ccpToAngle(ccp(vel.x, vel.y));
	//sprite.setRotation(-1 * Rad2Deg(angle));

	sprite.setRotation(body->GetAngle() * 180 / b2_pi);

	_window.draw(sprite);


}