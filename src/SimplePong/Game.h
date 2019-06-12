#pragma once
#include <SDL.h>

//Contains High level absraction of game code as declarations
struct Vector2
{
	float x;
	float y;

};

class Game
{
	public:
		
		Game();
		//Initialize the game

		bool Initialize();

		//Run game loop till game ends
		void RunLoop();

		//shutdown the game
		void Shutdown();

	private:
		//Helper functions for the game loop
		void ProcessInput();
		void UpdateGame();
		void GenerateOutput();

		//Window created by SDL, g is for game
		  SDL_Window* gWindow;

		//Renderer to adding graphics to game
		  SDL_Renderer* gRenderer;

		 //Is the game still running
		 bool stillRunning;

		Vector2 mPaddlePos;
		Vector2 mBallPos;
		Vector2 mBallVel;
		Vector2 mPaddlePos2;
		

		Uint32 mTickCount;

		 int mPaddleDir=0;
		 int mPaddleDir2=0;
	


};

