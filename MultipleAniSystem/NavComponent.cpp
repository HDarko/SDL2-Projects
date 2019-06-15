#include "NavComponent.h"
#include"Actor.h"
NavComponent::NavComponent(class Actor* owner, int updateOrder)
	:MoveComponent(owner, updateOrder),mAtPos{true}
{

}

void NavComponent::Update(float deltaTime)
{
	if (mAtPos)
	{
		// If ww arent at position, continue moving
		SetForwardSpeed(0.0f);
		
	}
	else {
		TurnTo(mLookPos);
	 }
	MoveComponent::Update(deltaTime);
}


void NavComponent::TurnTo(const Vector2& pos)
{
	// Vector from me to pos
	Vector2 dir = pos - mOwner->GetPosition();
	// New angle is just atan2 of this dir vector
	// (Negate y because +y is down on screen)
	float angle = Math::Atan2(-dir.y, dir.x);
	mOwner->SetRotation(angle);
}