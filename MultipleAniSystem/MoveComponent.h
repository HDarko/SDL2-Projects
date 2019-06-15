#pragma once
#include "Component.h"
class MoveComponent :
	public Component
{
public:
	//Lower update Order is needed to make sure it uodates first
	MoveComponent(class Actor* owner, int updateOrder = 10);
	void Update(float deltaTime) override;
	float GetForwardSpeed() const { return mForwardSpeed; }
	float GetAngularSpeed() const { return mAngularSpeed; }
	float SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }

private:
	//Rotation of actor(radians/second)
	float mAngularSpeed;
	//Forward speed of character (units/second)
	float mForwardSpeed;


};

