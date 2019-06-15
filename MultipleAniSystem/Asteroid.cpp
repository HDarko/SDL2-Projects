#include "Asteroid.h"
#include "Random.h"
#include "SpriteComponent.h"
#include "AnimSpriteComponent.h"
#include"Game.h"
#include "MoveComponent.h"


//I Call this asetoid but for the purposes of this demo
//This is the skeleton or sprite instead

Asteroid::Asteroid(Game* game, int state, Vector2 pos)
	:Actor(game)
{
	//Initialize to random positions and orientations
	//Vector2 randPos = Random::GetVector(Vector2::Zero, Vector2(1024.0f, 768.0f));
	SetPosition(pos);
	//SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	//Create a sprite Component and set Texture

	AnimSpriteComponent* sc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/CH/Character01.png"),
		game->GetTexture("Assets/CH/Character02.png"),
		game->GetTexture("Assets/CH/Character03.png"),
		game->GetTexture("Assets/CH/Character04.png"),
		game->GetTexture("Assets/CH/Character05.png"),
		game->GetTexture("Assets/CH/Character06.png"),
		game->GetTexture("Assets/CH/Character07.png"),
		game->GetTexture("Assets/CH/Character08.png"),
		game->GetTexture("Assets/CH/Character09.png"),
		game->GetTexture("Assets/CH/Character10.png"),
		game->GetTexture("Assets/CH/Character11.png"),
		game->GetTexture("Assets/CH/Character12.png"),
		game->GetTexture("Assets/CH/Character13.png"),
		game->GetTexture("Assets/CH/Character14.png"),
		game->GetTexture("Assets/CH/Character15.png"),
		game->GetTexture("Assets/CH/Character16.png"),
		game->GetTexture("Assets/CH/Character17.png"),
		game->GetTexture("Assets/CH/Character18.png"),
	};
	sc->SetAnimTextures(anims);
	sc->SetAnim("Walk", 0, 5,true);
	sc->SetAnim("Jump", 6, 14,false);
	sc->SetAnim("Punch", 15, 17,false);
	sc->SetAnim("JumpL", 6, 14, true);
	sc->SetAnim("PunchL", 15, 17, true);
	if (state == 1) {
		sc->SetCurAnim("Punch");
		sc->SetAnimFPS(1.0f);
	}
	if (state == 2)
	{
		sc->SetCurAnim("Walk");
		sc->SetAnimFPS(3.0f);
	}
	if (state == 4)
	{
		sc->SetCurAnim("JumpL");
		sc->SetAnimFPS(5.0f);
	}
	if (state == 5)
	{
		sc->SetCurAnim("PunchL");
		sc->SetAnimFPS(3.0);
	}
	//Create a input component

	//AddComponent(std::move(sc));
	//Create a move Component and set a forward Speed
	//MoveComponent* mc = new MoveComponent(this);
	//mc->SetForwardSpeed(150.0f);

}




