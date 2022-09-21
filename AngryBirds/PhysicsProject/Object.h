#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include <iostream>
#include <sstream>


class Object : public b2BodyUserData
{
public:
	Object(sf::Vector2f _position, float _scale, b2BodyType _bodyType, std::string _spriteName, b2World* _world);
	void CreatePhysics(sf::Vector2f _position, float _scale, b2BodyType _bodyType, b2World* _world);
	void Render(sf::RenderWindow& _window, float _scale);
	std::string spriteName = "";
	class MyListener : public b2ContactListener
	{
		void BeginContact(b2Contact* contact)
		{
			b2Fixture* fixtureA = contact->GetFixtureA();
			b2Fixture* fixtureB = contact->GetFixtureB();
			b2Body* body1 = fixtureA->GetBody();
			b2Body* body2 = fixtureB->GetBody();

			Object* object = (Object*)&(fixtureB->GetBody()->GetUserData());


			if (object != nullptr && object->body)
			{
				//std::cout << "started" << (object->isBird == true);
				//std::cout << "Bird" << object->isBird;
			}
		}

		void EndContact(b2Contact* contact)
		{
			//	std::cout << "ended\n";
		}
	};


	MyListener listener;
	bool isBird;
	//private:
		// Box 2D Stuff
	b2BodyDef bodyDef;
	b2Body* body;
	b2PolygonShape shape;
	b2FixtureDef fixtureDef;

	// SFML Stuff
	sf::Sprite sprite;
	sf::Texture texture;

};