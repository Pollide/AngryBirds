#pragma once

#include "SFML/Graphics.hpp"
#include "Listener.h"
#include "box2d/box2d.h"
#include <iostream>
#include <sstream>



class Object
{

public:


	struct FixtureUserData
	{
		int mObjectType{};
		b2Fixture* mOwningFixture{};
		Object* object;
	};

	//listens to every collision the object makes
	class Listener : public b2ContactListener
	{
	public:
		std::vector<std::unique_ptr<FixtureUserData>>* mFixtureUserData; //points to the level list

		void BeginContact(b2Contact* contact)
		{
			if (contact && contact->IsTouching())
			{
				for (int i = 0; i < mFixtureUserData->size(); ++i)
				{
					//check if first fixture is the bird
					if (mFixtureUserData->at(i)->mOwningFixture == contact->GetFixtureA() && !mFixtureUserData->at(i)->object->isBird)
					{
						for (int j = 0; j < mFixtureUserData->size(); ++j)
						{
							//check if second fixture is an object
							if (mFixtureUserData->at(j)->mOwningFixture == contact->GetFixtureB() && mFixtureUserData->at(j)->object->isBird)
							{
								//check if that object is not the ground and is alive (as poof is zero)
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

		//can check when the contact ends, but not in use right now
		void EndContact(b2Contact* contact)
		{

		}
	};

	Object(sf::Vector2f _position, float _scale, b2BodyType _bodyType, std::string _spriteName, b2World* _world, std::vector<std::unique_ptr<FixtureUserData>>* mFixtureUserData);


	void CreatePhysics(sf::Vector2f _position, float _scale, b2BodyType _bodyType, b2World* _world);
	void Render(sf::RenderWindow& _window, float _scale);
	void LoadTexture(std::string _spriteName);

	//listens to the collisions
	Listener listener;

	std::string spriteName;
	bool isBird; //is the object a bird?
	int PoofIndex; //gets the animation index
	int PoofTimer; //gets the time it takes to change animation frame

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