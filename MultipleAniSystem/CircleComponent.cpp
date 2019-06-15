#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(Actor* owner)
	:Component{ owner },
	mRadius{0.0f}
{}
const Vector2& CircleComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

float CircleComponent::GetRadius() const
{
	return mOwner->GetScale() * mRadius;
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	// Calculate distance of the vector from b to a squared
	Vector2 diff = a.GetCenter() - b.GetCenter();
	float distSq = diff.LengthSq();

	// Calculate sum of radius of the two circle
	float radiiSq = a.GetRadius() + b.GetRadius();
	radiiSq *= radiiSq;
	// if vector is smaller than sum of radi then they intersect
	return distSq <= radiiSq;
}
