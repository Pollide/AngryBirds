#pragma once
#include "box2d/box2d.h"
#include <iostream>
#include "Object.h"

struct MyFixtureUserDataType
{
	int mObjectType{};
	b2Fixture* mOwningFixture{};
};

class Listener : public b2ContactListener
{
public:
	std::vector<std::unique_ptr<MyFixtureUserDataType>>* mFixtureUserData;

	void BeginContact(b2Contact* contact)
	{
		// call the appropriate LevelObject's beginContact function

		if (contact && contact->IsTouching())
		{
			MyFixtureUserDataType* myData1 = (MyFixtureUserDataType*)&(contact->GetFixtureB()->GetUserData());
			//MyData* myData2 = (MyData*)&(contact->GetFixtureB()->GetUserData().pointer);
			//MyData B = static_cast<MyData>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

			//std::cout << "collide";
			//std::cout << "collide" << myData1->mOwningFixture;
			//std::cout << "size:" << mFixtureUserData->size();

			for (int i = 0; i < mFixtureUserData->size(); ++i)
			{
				//std::cout << "next" << mFixtureUserData->at(i)->mObjectType << "|";
				if (mFixtureUserData->at(i)->mOwningFixture == contact->GetFixtureA())
				{
					std::cout << "collide";
					//std::swap(mFixtureUserData[i], mFixtureUserData[mFixtureUserData.size() - 1]);
					//mFixtureUserData.pop_back();
					break;
				}
			}

			/*
			b2Fixture* fixtureA = contact->GetFixtureA();
			b2Fixture* fixtureB = contact->GetFixtureB();
			b2Body* body1 = fixtureA->GetBody();
			b2Body* body2 = fixtureB->GetBody();

			Object* object = (Object*)&(fixtureA->GetBody()->GetUserData());

			std::cout << "hi";
			object->Poof();
			if (object != nullptr && (((Object*)&fixtureA->GetBody()->GetUserData())->isBird == true || ((Object*)&fixtureB->GetBody()->GetUserData())->isBird == true))
			{
				//std::cout << "started" << (object->isBird == true);
				std::cout << (object->isBird == true ? "TRUE" : "false");
				object->Poof();
			}

			b2Fixture* fixtureA = contact->GetFixtureA();
			b2Fixture* fixtureB = contact->GetFixtureB();
			b2Body* body1 = fixtureA->GetBody();
			b2Body* body2 = fixtureB->GetBody();

			Object* object = (Object*)&(fixtureA->GetBody()->GetUserData());
			//Object* object = (Object*)&(contact->GetFixtureA()->GetBody()->GetUserData());
			//	Object* object = (Object*)&(contact->GetFixtureA()->GetBody()->GetUserData());
			//	Object B = static_cast<Object>(contact->GetFixtureB()->GetBody()->GetUserData());
				*/

				/*
				// turn fixtures into level objects
				LevelObject* A = static_cast<LevelObject*>
					(contact->GetFixtureA()->GetBody()->GetUserData());
				LevelObject* B = static_cast<LevelObject*>
					(contact->GetFixtureB()->GetBody()->GetUserData());

				// turn fixtures into player
				Player* player = dynamic_cast<Player*>(A);
				LevelObject* other = B;
				if (player == nullptr)
				{
					player = dynamic_cast<Player*>(B);
					other = A;
				}

				// call the begin contact
				if (A && B)
				{
					// always prefer to call the player's version of beginContact
					if (player && other)
						player->beginContact(other, contact);
					else
						A->beginContact(B, contact);
				}

				*/
		}
	}

	void EndContact(b2Contact* contact)
	{
		// nothing to do here for the current implementation
	}
};
