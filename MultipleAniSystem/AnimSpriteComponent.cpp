#include "AnimSpriteComponent.h"
#include <algorithm>
#include "Actor.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent{ owner, drawOrder }, mCurrFrame{ 0.0f }, mAnimFPS{ 8.0f }, mCurAnim{nullptr}
{

}

struct AnimwithFrames
{
	int animFrameStart{ 0 };
	int animFrameStop{ 0 };
	bool looping=false;

	//AnimwithFrames(std::string name, int  start, int stop,
	//bool loop)
	//	:animName{ name }, animFrameStart{ start }, animFrameStop{stop},
	//	 looping{loop}
	//{}
};

void AnimSpriteComponent::SetAnimTextures( std::vector<SDL_Texture*>& textures)
{

	mAnimTextures = std::move(textures);

	if(mAnimTextures.size()>0)
	{ 
		mCurrFrame = 0;
		SetTexture(mAnimTextures[0]);
	}
}

void AnimSpriteComponent::Update(float deltatime)
{
	//update the mCurFrame then make sure it is less
	//than num of textures (wrap back to beginiing if necessary)
	SpriteComponent::Update(deltatime);

	//Extra code to check the aimation 

	
	if (mAnimTextures.size() >0 and mCurAnim!=nullptr)
	{
		//update the current frame based on frame rate and delta time
		mCurrFrame += (mAnimFPS * deltatime);
	

			//wrap back if necessary
			if (mCurrFrame > (mCurAnim->animFrameStop)+1)
			{
				if (mCurAnim->looping)
				{
					mCurrFrame = mCurAnim->animFrameStart;
				}
				else
				{
					mCurrFrame = mCurAnim->animFrameStop;
				}
			}
		
		//Set the current texture
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	};
}
//Update animation frame (overriden from component)

void AnimSpriteComponent::SetAnim(std::string nameofAnim, int animStartInText, int animEndInText, bool looping)
{

	mAnims[nameofAnim] = new AnimwithFrames { animStartInText, animEndInText, looping };
	
}



AnimSpriteComponent::~AnimSpriteComponent()
{
	for ( auto text: mAnimTextures)
	{
		delete text;
	}
	for (auto anim : mAnims)
	{
		delete anim.second;
		anim.second = nullptr;
	}
	mAnimTextures.clear();
	mAnims.clear();

}

void AnimSpriteComponent::SetCurAnim(std::string nameofAnim)
{
	//std::vector<AnimSpriteComponent::AnimwithFrames*>::iterator animinVect;
	if (mAnims.find(nameofAnim) != mAnims.end())
	{
		mCurAnim = mAnims[nameofAnim];
		mCurrFrame= mCurAnim->animFrameStart;
	}
	else
	{
		SDL_Log("Anim does not exist: %s", SDL_GetError());
		mCurAnim = nullptr;
		mCurrFrame = 0;
	}
}




