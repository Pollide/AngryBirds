#include "Joint.h"


const float pi = 3.1415926f;
const float oneEighty = 180.0f;

float Rad2Deg(float rad)
{
	return rad * (oneEighty / pi);
}

Joint::Joint(Object* board, Object* wheel, b2Vec2 localAnchor, b2World* _world)
{
	b2DistanceJointDef distJointDef;
	//distJointDef.Initialize(body, wheelOne->body, b2Vec2(0.0f, 0.0f), b2Vec2(0, 0.0f));
	distJointDef.bodyA = wheel->body;
	distJointDef.bodyB = board->body;
	//distJointDef.length = 5;
	distJointDef.minLength = 0.01f;
	distJointDef.maxLength = 0.2f;
	distJointDef.localAnchorB = localAnchor;

	//distJointDef.collideConnected = true;
	b2DistanceJoint* r_joint = (b2DistanceJoint*)_world->CreateJoint(&distJointDef);
}

void Joint::Simulate()
{
	//this->setPosition(ccp(mBody->GetPosition().x * PTM_RATIO, mBody->GetPosition().y * PTM_RATIO));
	//b2Vec2 vel = mBody->GetLinearVelocity();
	//float angle = ccpToAngle(ccp(vel.x, vel.y));
	//this->setRotation(-1 * CC_RADIANS_TO_DEGREES(angle));
}
