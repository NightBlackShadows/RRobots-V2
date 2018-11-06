#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "Options.h"
#include "WindowHandler.h"

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
bool init();
void draw();
void close();


int main(int argc, char* args[]) {
	//Start up SDL and create window

	bool running = true;

	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		wh.initWindowHandler(gWindow);
		if (game.initGame(renderer,options)) {
			while (running) {
				/*
				//Event handler
				SDL_Event e;
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{

					//User requests quit
					if (e.type == SDL_QUIT)
					{
						running = false;
					}

				}*/
				running = game.runGame();
				
				draw();
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

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
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

	//Destroy window    
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}