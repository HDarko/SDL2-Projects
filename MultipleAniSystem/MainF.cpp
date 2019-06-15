#include <iostream>
#include <string>
#include <GL/glew.h>
#include "Game.h"

//SDL_Window* window;
SDL_GLContext glContext;

using namespace std;




//Initialize SDL2


// Create our window centered at 512x512 resolution
/*bool OpenGLInit()		
	{

		//Set our version of OpenGL
		SetOpenGLAttributes();
		// Create our window centered at 512x512 resolution
		window = SDL_CreateWindow( "My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			512,512, SDL_WINDOW_OPENGL);

			if (!window) { 
			cout << "Unable to create SDL2 Window" << endl;
			CheckSDLError(__LINE__);
			return false; 
						}
			
			//If everything is fine we creat our OpenGL context and attach to window created.
			glContext = SDL_GL_CreateContext(window);

			

			// This makes our buffer swap syncronized with the monitor's vertical refresh
			SDL_GL_SetSwapInterval(1);

			// Init GLEW
			// Apparently,apple step is needed for Apple.
			//#ifndef __APPLE__
			glewExperimental = GL_TRUE;
			glewInit();
			//#endif
			//And Done!
			return true;
}*/


int main(int argc, char * argv[])
{
	Game game;
	if (game.Initialize())
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
	
}

/*bool SetOpenGLAttributes()
{
	// Set our OpenGL version.
	// SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run 
	//I will be using 4.6 myself
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	// Turn on double buffering with a 24bit Z buffer.
	// You may need to change this to 16 or 32 for your system
	//Already on by default but good to know
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	return true;

}*/




/*void PrintSDL_GL_Attributes()
{
	int value = 0;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MAJOR_VERSION : " << value << std::endl;

	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MINOR_VERSION: " << value << std::endl;
}*/


		// Swap our back buffer to the front is what the SwapWindow does
		// This is the same as :
		// 		SDL_RenderPresent(&renderer);
	
