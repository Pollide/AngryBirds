#include "MouseJoint.h"

MouseJoint::MouseJoint(b2World* _world)
{
	
}

void MouseJoint::Bind(Bird* loadedBird, float x, float y, b2World* _world)
{
	b2MouseJointDef* mouseJointDef = new b2MouseJointDef();
	mouseJointDef->bodyA = body;
	mouseJointDef->bodyB = loadedBird->body;

	mouseJointDef->target.Set(x, y);
	mouseJointDef->maxForce = 5000.0;
	mouseJointDef->stiffness = 5;
	mouseJointDef->damping = 0.9;

	mouseJoint = (b2MouseJoint*)_world->CreateJoint(mouseJointDef);
}

void MouseJoint::CreateGroundBody(b2World* _world)
{
	body = _world->CreateBody(&bodyDef);
	//fixtureDef.shape = &shape;
	//shape.SetAsBox(1.0f, 1.0);
	
	//bodyDef.type = b2BodyType::b2_staticBody;
	
}

void MouseJoint::Update(float x, float y)
{
	b2Vec2 mouseWorld = b2Vec2(x, y);
	mouseJoint->SetTarget(mouseWorld);
}

void MouseJoint::Render(sf::RenderWindow& _window)
{
	//if (mouseJoint != NULL)
	//{
	//	b2Vec2 v1(0, 0);
	//	v1 = mouseJoint->GetAnchorA();
	//	b2Vec2 v2(0, 0);
	//	v2 = mouseJoint->GetAnchorB();

		//float startX = v1.x;
		//float startY = v1.y;
		//line[0].position = sf::Vector2f(startX, startY);
		//float endX = v2.x;
		//float endY = v2.y;
		//line[1].position = sf::Vector2f(endX, endY);
		//
		//_window.draw(line, 4, sf::Lines);
	//}
}

void MouseJoint::Destroy(b2World* _world)
{
	if (mouseJoint != NULL)
	{
		_world->DestroyJoint(mouseJoint);
		mouseJoint = NULL;
	}
}