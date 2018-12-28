#include <iostream>
#include <string>
#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#endif
#if defined __APPLE__ || defined __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif
#include "Game.h"
#include "Options.h"
#include "MusicHandler.h"
#include "WindowHandler.h"
#include "Timer.h"

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

SDL_Renderer* renderer = NULL;

Game game;
Options options;
WindowHandler wh;
MusicHandler mh;
bool init();
void draw();
void close();


int FPS_LOCK = 60;

int main(int argc, char* args[]) {
	//Start up SDL and create window

	bool running = true;
	//The frames per second timer
	Timer fpsTimer;

	//The frames per second cap timer
	Timer capTimer;


	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		wh.initWindowHandler(gWindow);
		if (game.initGame(renderer,options)) {

			//Start counting frames per second
			int countedFrames = 0;
			int SCREEN_TICKS_PER_FRAME = 1000 / FPS_LOCK;
			fpsTimer.start();
			while (running) {
				
				capTimer.start();
				running = game.runGame();

				//Calculate and correct fps
				float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
				if (avgFPS > 2000000)
				{
					avgFPS = 0;
				}

				draw();
				++countedFrames;
				//If frame finished early
				int frameTicks = capTimer.getTicks();
				if (frameTicks < SCREEN_TICKS_PER_FRAME)
				{
					//Wait remaining time
					SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
				}
			}
		}
		else {
			printf("could not init game\n");
		}
	}



	//Free resources and close SDL
	close();

	return 0;
}

void draw() {

	//Vill man testa att skriva ut något på bilden så gör det här!

	//SDL_RenderClear(renderer);
	//Update screen
	game.drawGame(renderer);

	SDL_RenderPresent(renderer);

}


bool init() {
	//Initialization flag
	bool success = true;

	options.loadOptions();
	FPS_LOCK = options.getFPSLock();
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (mh.initMusic()) {
			if (mh.loadMusic()) {
				mh.changeVolume(50);
				mh.playMusic();
			}
			else {
				printf("Some or all music could not be loaded\n");
			}
		}

		//Create window
		gWindow = SDL_CreateWindow("RRobot 2.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, options.getWidth(), options.getHeight(), SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			wh.initWindowHandler(gWindow);
			//Create renderer for window
			renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				else {
					wh.setFullscreen(options.getFullscreen());
				}
			}
		}
	}

	return success;
}

void close() {
	//Free loaded image
	//SDL_DestroyTexture(gTexture);
	//gTexture = NULL;

	game.~Game();
	options.~Options();
	mh.~MusicHandler();

	//Destroy window    
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
