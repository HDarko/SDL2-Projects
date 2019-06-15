#include "SpriteComponent.h"
#include "Game.h"

const float PI = 3.141592653589793238463f;


 SpriteComponent::SpriteComponent( Actor* owner,int drawOrder)
	 :Component{owner}, mTexture{ nullptr }, mDrawOrder{drawOrder},
	 mTexWidth{0}, mTexHeight{0}
{

	 mOwner->GetGame()->AddSprite(this);
}

 SpriteComponent::~SpriteComponent()
 {
	 mOwner->GetGame()->RemoveSprite(this);
 }
void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	//Get width/height of texture

	SDL_QueryTexture(texture, NULL, nullptr, &mTexWidth, &mTexHeight);

	
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{

	if (mTexture)
	{
		SDL_Rect r;
		// Scale the width/height by owner's scale
		r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
		r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
		// Center the rectangle around the position of the owner
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

		// Draw (have to convert angle from radians to degrees, and ftom clockwise to counter since positve
		//angles are clockwise in SDL but counter clockwise in unit circle thus megate the angle)
		//use negative degreses since the unit cirle is counterclockwise while the angle we have
		//is clockwise
		float degrees = mOwner->GetRotation() * (180.0 / PI);
		//renderer,source rectangle,destination rect,angle,point of rotation,flip behaviour
		SDL_RenderCopyEx(renderer, mTexture,nullptr,&r,
			-degrees,
			nullptr,
			SDL_FLIP_NONE);
	}
};