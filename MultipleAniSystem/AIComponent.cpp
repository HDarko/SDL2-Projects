#include "AIComponent.h"
#include "AIState.h"
#include"Actor.h"
#include "SDL_Log.h"

AIComponent::AIComponent(Actor* owner)
	:Component(owner), mCurrentState{ nullptr }
{

}

void AIComponent::Update(float deltaTime)
{
	if (mCurrentState)
	{
		mCurrentState->Update(deltaTime);
	}
}

void AIComponent::ChangeState(const std::string& name)
{
	//Exit the current state
	if (mCurrentState)
	{
		mCurrentState->OnExit();
	}

	//Search for the state associated with name
	auto iter = mStateMap.find(name);
	if (iter != mStateMap.end())
	{
		mCurrentState = iter->second;
		// We're entering the new state
		mCurrentState->OnEnter();
	}
	else
	{
		//Could not find the state associated with name
		SDL_Log("Could not find AIState %s in state map", name.c_str());
		mCurrentState = nullptr;
	}
}

 void AIComponent::RegisterState(AIState* state)
{
	mStateMap.emplace(state->GetName(), state);
}