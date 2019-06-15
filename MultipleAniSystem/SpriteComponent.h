#pragma once
#include "Component.h"
#include <SDL.h>
class SpriteComponent: public Component
{
public:
	//Lower the drawerOrder the further back the sprite is in the screen
	//100 coresponds to background

	SpriteComponent(class Actor* owner, int drawOrder = 100);

	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);
	//Assigns the Texture/Image to the Actor
	virtual void SetTexture(SDL_Texture* texture);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }

protected:
	//Texture to draw
	SDL_Texture* mTexture;
	//Draw order in painter's algorithm
	int mDrawOrder;
	//Width and Height of Texture

	int mTexWidth;
	int mTexHeight;

	
};
