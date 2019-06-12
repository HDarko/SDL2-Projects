#include "Game.h"
#include <SDL.h>

const int wallthickness{15};
const int paddleH{60};

 Game::Game()
	 :
	 gWindow{ nullptr },
	 stillRunning{ true },
	 gRenderer{ nullptr },
	 mPaddleDir{0},
	 mTickCount{ 0 },
	 mBallVel{200.0f,235.0f}
	{

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
	 gWindow = SDL_CreateWindow("Pong", 100, 100, 1024, 768, 0);

	 if (!gWindow)
	 {
		 SDL_Log("Failed to create a SDL window: %s", SDL_GetError());
		 return false;
	 };
	 //enabling vsync and taking advatage of graphics hardware
	 gRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC);
	 if (!gRenderer)
	 {
		 SDL_Log("Failed to create a SDL renderer: %s", SDL_GetError());
		 return false;
	 }
	 //Initialize the struct values
	 mPaddlePos.x = 30;
	 mPaddlePos2.x = 994;
	 mPaddlePos.y = 384;
	 mPaddlePos2.y = 384;
	 mBallPos.x = 512;
	 mBallPos.y = 384;
	 return true;
 }

void Game::Shutdown()
	{
	SDL_DestroyRenderer(gRenderer);
		SDL_DestroyWindow(gWindow);
		SDL_Quit();
	}

void Game::RunLoop()
	{
		while (stillRunning)
		{
			ProcessInput();
			UpdateGame();
			GenerateOutput();
		}
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
	}
	//Get entire Keyboard state
		const Uint8* keyboardstate = SDL_GetKeyboardState(NULL);
		
		if (keyboardstate[SDL_SCANCODE_ESCAPE])
		{
			stillRunning = false;
		}
		mPaddleDir = 0;
		mPaddleDir2 = 0;
		if (keyboardstate[SDL_SCANCODE_W])
		{
			mPaddleDir -= 1;
		}

		if (keyboardstate[SDL_SCANCODE_S])
		{
			mPaddleDir += 1;
		}
		if (keyboardstate[SDL_SCANCODE_I])
		{
			mPaddleDir2 -= 1;
		}

		if (keyboardstate[SDL_SCANCODE_K])
		{
			mPaddleDir2 += 1;
		}

	
}

void Game::GenerateOutput()
{

	//Create the background colour
	SDL_SetRenderDrawColor(gRenderer, 128, 128, 128, 255);
	SDL_RenderClear(gRenderer);

	//Creating shapes for Pong

	//----------------Walls-----------------------
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
	
	SDL_Rect Wall{ 0,0,1024,wallthickness };

	SDL_RenderFillRect(gRenderer, &Wall);

	SDL_Rect Wall2{ 0,768 - wallthickness,1024,wallthickness };

	SDL_RenderFillRect(gRenderer, &Wall2);
	//Right wall is now a space for player2
	//SDL_Rect Wall3{ 1024-wallthickness,0,wallthickness,768 };

	//SDL_RenderFillRect(gRenderer, &Wall3);

	SDL_Rect ball{ static_cast<int>(mBallPos.x - wallthickness / 2),
		static_cast<int>(mBallPos.y - wallthickness / 2), wallthickness, wallthickness };

	SDL_RenderFillRect(gRenderer, &ball);
	//Since a rect is drawing using its top left edge but we stared the centers in Game
	//we must account for that.
	SDL_Rect paddle{ static_cast<int>(mPaddlePos.x-wallthickness/2), static_cast<int>(mPaddlePos.y - paddleH/2),
		wallthickness, static_cast<int>(paddleH) };
	SDL_Rect paddle2{ static_cast<int>(mPaddlePos2.x-wallthickness/2), static_cast<int>(mPaddlePos2.y - paddleH / 2),
		wallthickness, static_cast<int>(paddleH) };

	SDL_RenderFillRect(gRenderer, &paddle);
	SDL_RenderFillRect(gRenderer, &paddle2);
	//Swap front and back buffers in SDL
	SDL_RenderPresent(gRenderer);
}

	

void Game::UpdateGame()
{

	//wait till at least 16ms has passed then go past this frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16));
	{
		//Thinking of time in seconds rather than in frames we use delta time to makeup
		//for difference in frames which is number of thicks since last frame

		//ticks are in miliseconds so transform into secs by division of 10^3
		float deltaTime = (SDL_GetTicks() - mTickCount) / 1000.0f;


		//clamp the maximun delta time just in case increases substatially due to debugging or other reasons
		if (deltaTime > 0.05f)
		{
			deltaTime = 0.05f;
		}

		//Update tick counts for the next frame as GetTicks counts ticks from Game init to current

		mTickCount = SDL_GetTicks();



		//Update world with deltatime
		//----------Update Paddle movement
		if (mPaddleDir != 0)
		{
			//speed of 300pixels/sec
			mPaddlePos.y += mPaddleDir * 230.0f * deltaTime;

			//Prevent paddle from leaving boundary
			//if paddle is at bottom and trying to leave screen
			if (mPaddlePos.y < (paddleH / 2.0f + wallthickness))
			{
				mPaddlePos.y = paddleH / 2.0f + wallthickness;
			}
			//if paddle is at the top and trying to leave screen
			else if (mPaddlePos.y > (768.0f - paddleH / 2.0f - wallthickness))
			{
				mPaddlePos.y = 768.0f - paddleH / 2.0f - wallthickness;
			}
		}

		//----------Same functionality for player 2
		if (mPaddleDir2 != 0)
		{
			//speed of 300pixels/sec
			mPaddlePos2.y += mPaddleDir2 * 230.0f * deltaTime;

			//Prevent paddle from leaving boundary
			//if paddle is at bottom and trying to leave screen
			if (mPaddlePos2.y < (paddleH / 2.0f + wallthickness))
			{
				mPaddlePos2.y = paddleH / 2.0f + wallthickness;
			}
			//if paddle is at the top and trying to leave screen
			else if (mPaddlePos2.y > (768.0f - paddleH / 2.0f - wallthickness))
			{
				mPaddlePos2.y = 768.0f - paddleH / 2.0f - wallthickness;
			}
		}
		mBallPos.x += mBallVel.x*deltaTime;
		mBallPos.y += mBallVel.y*deltaTime;

		//Did the ball collide with the top wall and is it heading downing after
		//remember 0,0 is up and 0,768 is down for y
		if (mBallPos.y <= wallthickness && mBallVel.y < 0.0f)
		{
			mBallVel.y *= -1;
		}
		//did the ball colide with bottom wall
		if (mBallPos.y >= (768-wallthickness) && mBallVel.y > 0.0f)
		{
			mBallVel.y *= -1;
		}
		//Did the ball collidd with the paddle
		//check aboslute diff beteen paddle and ball y's
		//if greater than half paddle height then ball is too far
		float ydiff = mPaddlePos.y - mBallPos.y;
		ydiff = (ydiff > 0.0f) ? ydiff : -ydiff;
		if ((ydiff <= paddleH / 2.0f) &&
			//check if the	ball lines up with the paddle x position
			mBallPos.x <= 35.0f && mBallPos.x >= 30.0f &&
			//is ball moving to the left
			mBallVel.x < 0.0f)
		{
			mBallVel.x *= -1.0f;
		}
		//Same functionality for Paddle2 or player2
		float ydiff2 = mPaddlePos2.y - mBallPos.y;
		ydiff2 = (ydiff2 > 0.0f) ? ydiff2 : -ydiff2;
		if ((ydiff2 <= paddleH / 2.0f) &&
			//check if the	ball lines up with the paddle x position
			mBallPos.x >= 981.0f && mBallPos.x <= 1001.0f &&
			//is ball moving to the Right
			mBallVel.x > 0.0f)
		{
			mBallVel.x *= -1.0f;
		}
		// Did the ball go off the screen? (if so, end game)
		else if (mBallPos.x <= 0.0f || mBallPos.x >= 1034.0f)
		{
			stillRunning = false;
		}
		// Did the ball collide with the right wallIf P2 not there
		/*else if (mBallPos.x >= (1024.0f - wallthickness) && mBallVel.x > 0.0f)
		{
			mBallVel.x *= -1.0f;
		}
		*/	

	}
	


}
