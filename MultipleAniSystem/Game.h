#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include <string>
#include <vector>
#include "Actor.h"
#include "SpriteComponent.h"
#include"math.h"



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

		//Actor functions

		void AddActor(class Actor* actor);

		void RemoveActor(class Actor* actor);

		//Texture and Image functions
		/*Get the texture from either the map or load one from the file 
		and add to map then return*/
		SDL_Texture* GetTexture(const std::string& fileName);

		//Sprite function

		void AddSprite(SpriteComponent* sprite);

		void RemoveSprite(SpriteComponent* sprite);

	private:
		//Find the file and turn it into a texture 
		SDL_Texture* LoadTexture(const char* filename);

		//Load all the actors into the game.
		void LoadData();

			//Unload all the actors from game
		void UnloadData();

		//Actors that are active in the game right now
		std::vector<Actor*> mActors;

		/*Pending actors that where created while
		updating active actors and thus must wait for active actors or to finish update
		then are added to the above list or vector */
		std::vector<Actor*> mPendingActors;

		//Map of texture in the game
		std::unordered_map<std::string, SDL_Texture* > mTextures;

		// The sprite components of game
		std::vector<class SpriteComponent*> mSprites;

	


		//Helper functions for the game loop
		void ProcessInput();
		void UpdateGame();
		void GenerateOutput();

		//Window created by SDL, g is for game
		  SDL_Window* mWindow;

		//Renderer to adding graphics to game
		  SDL_Renderer* mRenderer;

		 //Is the game still running
		 bool stillRunning;

		 //Is the list of Actors still updating
		 bool mUpdatingActors;

		 //TargetFPS
		 const int mFPS;

		 int mFrameDelay;

		Uint32 mTicksCount;

		

	


};

