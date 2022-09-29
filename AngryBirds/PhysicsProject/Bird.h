// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name : Bird.h
// Description: Used to apply parameters to objects of type bird. Which type of bird, the corresponding sprite and its status. Also has render function.
// Authors: Pol & Allister

#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include "Object.h"

class Bird : public Object
{
public:
	Bird(int _type, bool _waiting = false);

	sf::String ReturnTextureName(int _type);

	void Render(sf::RenderWindow& _window, float _scale);

	bool waiting;
};