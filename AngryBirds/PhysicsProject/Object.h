#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include <iostream>
#include <sstream>
#include <cmath>


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
					if (mFixtureUserData->at(i)->mOwningFixture == contact->GetFixtureA())
					{
						Object* otherObject = mFixtureUserData->at(i)->object;


						for (int j = 0; j < mFixtureUserData->size(); ++j)
						{
							//check if second fixture is an object

							if (mFixtureUserData->at(j)->mOwningFixture == contact->GetFixtureB())
							{

								Object* thisObject = mFixtureUserData->at(j)->object;

								thisObject->contacted = true;

								//check if that object is not the ground and is alive (as poof is zero)
								if (thisObject->PoofIndex == 0 && otherObject->PoofIndex == 0)
								{
									if (otherObject->bodyDef.type == b2BodyType::b2_dynamicBody)
									{
										if (thisObject->CharacterType > 0)
										{
											//std::cout << "collide";
											b2Vec2 velocity = thisObject->body->GetLinearVelocity();

											float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);


											//std::cout << speed << ">" << otherObject->SpeedToDestroy << "|";

											if (otherObject->CharacterType == 0 ? ReturnSpeed(thisObject->body) >= otherObject->SpeedToDestroy : true)
											{

												otherObject->PoofIndex = 1;

												if (otherObject->CharacterType > 0)  //if both birds collide with eachother, they both die
													thisObject->PoofIndex = 1;
											}
										}
									}
									else
									{


										if (thisObject->CharacterType < 0)
										{
											thisObject->PoofIndex = 1;
										}
									}
								}
							}
						}
					}
				}
			}
		}

		//can check when the contact ends
		void EndContact(b2Contact* contact)
		{
			for (int j = 0; j < mFixtureUserData->size(); ++j)
			{
				//check if second fixture is an object

				if (mFixtureUserData->at(j)->mOwningFixture == contact->GetFixtureB())
				{
					mFixtureUserData->at(j)->object->contacted = false;
				}
			}
		}
	};

	Object(sf::Vector2f _position, float _scale, b2BodyType _bodyType, std::string _spriteName, b2World* _world, std::vector<std::unique_ptr<FixtureUserData>>* mFixtureUserData, int characterType, int speedToDestroy = 0);
	void CreatePhysics(sf::Vector2f _position, float _scale, b2BodyType _bodyType, b2World* _world);
	void Render(sf::RenderWindow& _window, float _scale);
	void LoadTexture(std::string _spriteName);

	static float ReturnSpeed(b2Body* body);

	//listens to the collisions
	Listener listener;
	bool contacted;
	int CharacterType;
	int SpeedToDestroy;

	//-1 - Normal enemy
	//0  - obstacle
	//3 - speed ability
	//2 - split ability
	//1 - Normal ability

	int hitpoints = 1;
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