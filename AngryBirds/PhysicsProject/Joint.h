#pragma once
#include "Object.h"

class Joint
{
public:
	Joint(Object* board, Object* wheel, b2Vec2 localAnchor, b2World* _world, int jointType);

	void Simulate();
};