#pragma once

#include "SFML/Graphics.hpp"
#include "Listener.h"
#include "box2d/box2d.h"
#include <iostream>
#include <sstream>



class Object
{

public:


	struct MyFixtureUserDataType
	{
		int mObjectType{};
		b2Fixture* mOwningFixture{};
		Object* object;
	};

	class Listener : public b2ContactListener
	{
	public:
		std::vector<std::unique_ptr<MyFixtureUserDataType>>* mFixtureUserData;

		void BeginContact(b2Contact* contact)
		{
			if (contact && contact->IsTouching())
			{
				for (int i = 0; i < mFixtureUserData->size(); ++i)
				{
					if (mFixtureUserData->at(i)->mOwningFixture == contact->GetFixtureA() && !mFixtureUserData->at(i)->object->isBird)
					{
						for (int j = 0; j < mFixtureUserData->size(); ++j)
						{
							if (mFixtureUserData->at(j)->mOwningFixture == contact->GetFixtureB() && mFixtureUserData->at(j)->object->isBird)
							{
								if (mFixtureUserData->at(i)->object->bodyDef.type == b2BodyType::b2_dynamicBody && mFixtureUserData->at(i)->object->PoofIndex == 0)
								{
									//std::cout << "collide";
									mFixtureUserData->at(i)->object->PoofIndex = 1;
									break;
								}
							}
						}
					}
				}
			}
		}

		void EndContact(b2Contact* contact)
		{
			// nothing to do here for the current implementation
		}
	};

	Object(sf::Vector2f _position, float _scale, b2BodyType _bodyType, std::string _spriteName, b2World* _world, std::vector<std::unique_ptr<MyFixtureUserDataType>>* mFixtureUserData);


	Listener listener;


	void CreatePhysics(sf::Vector2f _position, float _scale, b2BodyType _bodyType, b2World* _world);
	void Render(sf::RenderWindow& _window, float _scale);
	void LoadTexture(std::string _spriteName);

	bool isBird;
	int PoofIndex;
	int PoofTimer;
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