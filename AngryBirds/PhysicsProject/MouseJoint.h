#pragma once
#include "Bird.h"

class MouseJoint
{
public:
	MouseJoint(b2World* _world);
	void Bind(Bird* loadedBird, float x, float y, b2World* _world);
	void CreateGroundBody(b2World* _world);
	void Update(float x, float y);
	void Render(sf::RenderWindow& _window);
	void Destroy(b2World* _world);

	b2BodyDef bodyDef;
	b2Body* body;
	b2PolygonShape shape;
	b2FixtureDef fixtureDef;
	b2MouseJoint* mouseJoint;
	sf::Vertex line[2];

};