#include "MoveComponent.h"
#include "Math.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder), mAngularSpeed{0.0f}, mForwardSpeed{0.0f}
{

}
void MoveComponent::Update(float deltaTime) 
{
	//Set rotation if AngularSpeed is not Zero
	if (!Math::NearZero(mAngularSpeed))
	{
		float actorRotate = mOwner->GetRotation();
		actorRotate += mAngularSpeed * deltaTime;
		mOwner->SetRotation(actorRotate);
	}
	//Move the actor
	if (!Math::NearZero(mForwardSpeed))
	{
		Vector2 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;

		// (Screen wrapping code. Use onyl for androids then comment out)
		if (pos.x < 0.0f) { pos.x = 1022.0f; }
		else if (pos.x > 1024.0f) { pos.x = 2.0f; }

		if (pos.y < 0.0f) { pos.y = 766.0f; }
		else if (pos.y > 768.0f) { pos.y = 2.0f; }

		mOwner->SetPosition(pos);
	}

}
