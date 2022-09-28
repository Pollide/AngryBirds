#include "Object.h"
#include <iostream>


Object::Object(sf::Vector2f _position, float _scale, b2BodyType _bodyType, std::string _spriteName, b2World* _world, std::vector<std::unique_ptr<FixtureUserData>>* mFixtureUserData, int characterType, int speedToDestroy)
{
	// Sprite Setup
	LoadTexture(_spriteName);
	listener.mFixtureUserData = mFixtureUserData;
	CharacterType = characterType;
	SpeedToDestroy = speedToDestroy;
	if (_world != NULL) //if it isnt NULL, then this is an object, else it would be a bird
	{
		CreatePhysics(_position, _scale, _bodyType, _world);
	}
}


void Object::CreatePhysics(sf::Vector2f _position, float _scale, b2BodyType _bodyType, b2World* _world)
{

	shape.SetAsBox(sprite.getOrigin().x / _scale, sprite.getOrigin().y / _scale);

	fixtureDef.shape = &shape;


	if (CharacterType > 0)
	{
		//circleShape.m_radius = (texture.getSize().x / 2) / _scale;
		fixtureDef.density = 5.0f;
	}
	else
	{
		fixtureDef.restitution = 0.8f; // Bounce

		fixtureDef.density = SpeedToDestroy + 1;
	}

	bodyDef.position = b2Vec2(_position.x / _scale, _position.y / _scale);
	bodyDef.type = _bodyType;
	if (_world != NULL)
	{
		auto myUserData = std::make_unique<FixtureUserData>();
		myUserData->mObjectType = listener.mFixtureUserData->size(); // whatever this fixture is about
		myUserData->object = this;

		_world->SetContactListener(&listener);
		body = _world->CreateBody(&bodyDef);
		myUserData->mOwningFixture = body->CreateFixture(&fixtureDef);

		listener.mFixtureUserData->emplace_back(std::move(myUserData));
	}
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

void Object::LoadTexture(std::string _spriteName)
{
	texture.loadFromFile("Resources/" + _spriteName);
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

float Object::ReturnSpeed(b2Body* _body)
{
	b2Vec2 velocity = _body->GetLinearVelocity();

	float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);

	return speed;
}
