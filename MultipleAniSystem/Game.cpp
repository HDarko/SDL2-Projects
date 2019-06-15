#include "Game.h"
#include "Asteroid.h"
#include "Random.h"




const int wallthickness{15};
const int paddleH{60};

 Game::Game()
	 :
	 mWindow{ nullptr },
	 stillRunning{ true },
	 mRenderer{ nullptr },
	 mUpdatingActors{false},
	 mTicksCount{ 0 },
	 mFPS{60}
	{
	 mFrameDelay = 1000 / mFPS;
	}

 //Create necessary componnents for starting a game.
 bool Game::Initialize()
 {
	 int sdlStart{ SDL_Init(SDL_INIT_VIDEO) };
	 if (sdlStart != 0)
	 {
		 SDL_Log("SDL Initialization failed: %s", SDL_GetError());
		 return false;
	 }
	 mWindow = SDL_CreateWindow("Chapter 2", 100, 100, 1024, 768, 0);

	 if (!mWindow)
	 {
		 SDL_Log("Failed to create a SDL window: %s", SDL_GetError());
		 return false;
	 };
	 //enabling vsync and taking advatage of graphics hardware
	 mRenderer = SDL_CreateRenderer(mWindow,-1,SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC);
	 if (!mRenderer)
	 {
		 SDL_Log("Failed to create a SDL renderer: %s", SDL_GetError());
		 return false;
	 }
	

	 //Initialize SDL Image with PNG file format support
	 if (IMG_Init(IMG_INIT_PNG) == 0)
	 {
		 SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		 return false;
	 }

	 Random::Init();

	 LoadData();

	 mTicksCount = SDL_GetTicks();

	 return true;
 }



 void Game::RunLoop()
 {
	 while (stillRunning)
	 {
		Uint32 frameStart{ SDL_GetTicks() };
		 ProcessInput();
		 UpdateGame();
		 GenerateOutput();
		 //If frame is complete in less time that
		 //interval expected for FPS then wait for 
		 //remaing time
		 Uint32 frameTime=SDL_GetTicks()- frameStart;
		 if (mFrameDelay>frameTime)
		 {
			 SDL_Delay(mFrameDelay - frameTime);
		 }
	 }
 }

void Game::Shutdown()
	{
	//Delete all actors in the game
	while (!mActors.empty())
	{
		delete mActors.back();
	}
	//Finish the rest
	SDL_DestroyRenderer(mRenderer);
		SDL_DestroyWindow(mWindow);
		SDL_Quit();
	}

void Game::AddActor(Actor* actor)
{
	//If updating actors, need to add to pending Actor vector

	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}

	else
		//add to Actors vector
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	//Check Pending vector for actor first

	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// Swap the actor with the last actor in the list and pop it off (avoid erase copies)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}
	else {
		//hopefully else works
		// Checking Actor list next
		iter = std::find(mActors.begin(), mActors.end(), actor);
		if (iter != mActors.end())
		{
			// Swap to end of vector and pop off (avoid erase copies)
			std::iter_swap(iter, mActors.end() - 1);
			mActors.pop_back();
		}
	}
}

void Game::LoadData()

{
	// Create asteroids

	
		//new Asteroid(this);
		AddActor(std::move(new Asteroid(this, 1, Vector2{ 200,400 })));
		AddActor(std::move(new Asteroid(this, 2, Vector2{ 280,400 })));
		AddActor(std::move(new Asteroid(this, 3, Vector2{ 380,400 })));
		AddActor(std::move(new Asteroid(this, 4, Vector2{ 480,400 })));
		AddActor(std::move(new Asteroid(this, 5, Vector2{ 580,400 })));
	
}


void Game::UnloadData()
{
	// Delete actors
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// Destroy textures
	for (auto tex : mTextures)
	{
		SDL_DestroyTexture(tex.second);
	}
	mTextures.clear();
}


SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* text = nullptr;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{	
		//iter is a (ket,value) pair
		text = iter->second;
	}

	else
	{
		//c_str reutrns a pointer to an array that contains 
		//a null-terminated sequence of characters (i.e., a C-string) 
		//from std::string
		text = Game::LoadTexture(fileName.c_str());
		mTextures.emplace(fileName.c_str(), text);
	}

	return text;

}

void Game::AddSprite(SpriteComponent* sprite)
{
	//Find the insertion point in the sorted vector
	//the first element with a higher draw order than me

	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}
	//inserts element before position of iterator
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

SDL_Texture* Game::LoadTexture( const char* filename)
{
	//Load an image from a file then return that file as an SDL Surface pointer

	SDL_Surface* surf = IMG_Load(filename);

	if (!surf)
	{
		SDL_Log("Failed to log Texture file and returned a nullptr for %s", filename);
		return nullptr;
	}

	//Convert an SDL surface into Texture which SDL needs for drawing.
	SDL_Texture* text = SDL_CreateTextureFromSurface(mRenderer,surf);
	SDL_FreeSurface(surf);
	if (!text)
	{
		SDL_Log("Failed to convert surface to texture for %s", filename);
		return nullptr;
	}
	return text;


}

void Game::ProcessInput()
{
	SDL_Event event;
	/*As long as there is an event, then SDL will add it to the queue so
	always check if there is event in queue,use pointers*/
	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			//Handle different event types
		case SDL_QUIT:
			stillRunning = false;
			break;
		}

		const Uint8* keyState = SDL_GetKeyboardState(NULL);
		if (keyState[SDL_SCANCODE_ESCAPE])
			{
				stillRunning = false;
			}
		mUpdatingActors = true;
		for (auto actor : mActors)
		{
			actor->ProcessInput(keyState);
		}
		mUpdatingActors = false;
	}
	
	
}

void Game::GenerateOutput()
{

	//Create the background colour
	SDL_SetRenderDrawColor(mRenderer, 128, 128, 128, 255);
	SDL_RenderClear(mRenderer);

	//Creating shapes for Pong

	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}


	//Swap front and back buffers in SDL
	SDL_RenderPresent(mRenderer);
}

	

void Game::UpdateGame()
{

	//wait till at least 16ms has passed then go past this frame[Using different method now for
	//frame limiting]
	//while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

		//Thinking of time in seconds rather than in frames we use delta time to makeup
		//for difference in frames which is number of thicks since last frame

		//ticks are in miliseconds so transform into secs by division of 10^3
		float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;


		//clamp the maximun delta time
		if (deltaTime > 0.05f)
		{
			deltaTime = 0.05f;
		}

		//Update tick counts for the next frame as GetTicks counts ticks from Game init to current

		mTicksCount = SDL_GetTicks();

		//Deal with Actors

		mUpdatingActors = true;
		for (auto actor : mActors)
		{
			actor->Update(deltaTime);
		}
		mUpdatingActors = false;

		//Move any pending actors to mActors
		for (auto pendActor : mPendingActors)
		{
			mActors.emplace_back(pendActor);
		}
		mPendingActors.clear();

		//Now add any dead Actor to a vector for destruction
		std::vector<Actor*> destroyActors;
		for (auto actor : mActors)
		{
			if (actor->GetState() == Actor::EDead)
			{
				destroyActors.emplace_back(actor);
			}
		}

		//Delete each dead actor which are pointers so dissapear from mActors

		for (auto actor : destroyActors)
		{
			delete actor;
		}
}



