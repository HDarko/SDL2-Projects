#pragma once
#include "Component.h"
#include <unordered_map>
#include <string>
class AIComponent :
	public Component
{
	AIComponent(Actor* mOwner);
	void Update(float deltaTime) override;
	void ChangeState(const std::string& toState);

	//Add a new state to the map
	void RegisterState(class AIState* newState);

	private:
		//Maps name of state to AIState instance
		std::unordered_map<std::string, class AIState*> mStateMap;
		//Current State of Actor
		class AIState* mCurrentState;
};

