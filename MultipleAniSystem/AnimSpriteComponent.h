#pragma once
#include "SpriteComponent.h"
#include <vector>
#include<string>
#include<unordered_map>
class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder=100 );


		//Update animation frame (overriden from component)
		void Update(float deltatime) override;

	//Set the textures used for animation

	void SetAnimTextures( std::vector<SDL_Texture*>& textures);

	//Set or get the animation FPS
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float newFPS) { mAnimFPS = newFPS; }
	void SetAnim(std::string nameofAnim, int animStartInText, int animEndInText, bool looping);

	void SetCurAnim(std::string animeName);

	

	~AnimSpriteComponent();

	AnimSpriteComponent* GetSpriteComp() { return this; }
private:
	//All textures in the animation.
	std::vector<SDL_Texture*> mAnimTextures;
	//vector of name of animation and its texture range
	std::unordered_map<std::string , struct AnimwithFrames*> mAnims;
	//current frame displayed
	float mCurrFrame;
	//Animation frame rate
	float mAnimFPS;
	struct AnimwithFrames* mCurAnim;

	
};

