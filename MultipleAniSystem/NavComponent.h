#pragma once
#include "MoveComponent.h"
#include "Math.h"
class NavComponent :
	public MoveComponent
{
	//This component shall be used to point the direction
	//the AI actor should look at
	// Lower update order to update first
	NavComponent(class Actor* owner, int updateOrder = 10);
	void Update(float deltaTime) override;
	void TurnTo(const Vector2& pos);
	void SetLookAt(Vector2 pos) { mLookPos = pos; }
	Vector2& GetLookAt() { return mLookPos; }
private:
	Vector2 mLookPos;
	bool mAtPos;
};

