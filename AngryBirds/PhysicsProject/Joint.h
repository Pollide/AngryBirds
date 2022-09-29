// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name :  
// Description:  
// Authors:

#pragma once
#include "Object.h"

class Joint
{
public:
	Joint(Object* board, Object* wheel, b2Vec2 localAnchor, b2World* _world, int jointType);

	void Simulate();
};