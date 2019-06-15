#pragma once
#include <vector>
#include "Math.h"
class Actor
{
public:
	//Used to track state of the actor 
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	//Constructor/Destructor
	
	Actor(class Game* game);

	virtual ~Actor();

	//Update function is called from Game (not overridable)

	void Update(float deltaTime);

	//Updates all the components attached to the actor (not overridable)

	void UpdateComponents(float deltaTime);

	//Any actor-specific update code (is overridable)

	virtual void UpdateActor(float deltaTime);

	//Getters and Setters

    Vector2& GetPosition() { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	//Get actor's forward facing vector based on current Rotation.
	//Since SDL2 2D graphics uses +y as going down while unity circle uses
	//+y as going up we need to negate the y value
	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	 Game* GetGame() { return mGame; }

	//Input functions
	//ProcessInput function from Game(not overridable)
	void ProcessInput(const uint8_t* keyState);
	//Any actor-specific input code (overridable)
	virtual void ActorInput(const uint8_t* keyState);
	//Add/Remove componenets
	void AddComponent(class Component* component);

	void RemoveComponent(class Component* component);

	//Create a get any Component function;



private:

		//Actor's state
		State mState;

		//Transform Component

		//Center position of actor
		 Vector2 mPosition;

		//Uniform scale of actor (1.0f for 100%)
		float mScale;
		//Rotation angle (in radians)
		float mRotation;

		//Components held by this actor
		std::vector<class Component*> mComponents;

		//Game Actor is part of
		class Game* mGame;
};
