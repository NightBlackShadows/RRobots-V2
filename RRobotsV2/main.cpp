#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Board.h"
#include "Character.h"

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

SDL_Renderer* renderer = NULL;

Board board;

bool init();
bool loadMedia(Character* drow);
void draw(Character* drow);
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

		Character drow("resources/Characters/drow_male2.png", 32, 48, 4, 4);
		//Load media
		if (!loadMedia(&drow))
		{
			printf("Failed to load media!\n");
		}
		else
		{


			//Apply the image
			//SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
			//Update the surface
			//SDL_UpdateWindowSurface(gWindow);      

			//Event handler
			SDL_Event e;
			while (running) {
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{

					//User requests quit
					if (e.type == SDL_QUIT)
					{
						running = false;
					}

				}
				draw(&drow);
			}
		}
		drow.~Character();
	}

	

	//Free resources and close SDL
	close();

	return 0;
}

void draw(Character* drow) {

	//Vill man testa att skriva ut något på bilden så gör det här!

	//SDL_RenderClear(renderer);

	//Draws the map
	for (int y = 0; y < BOARDHEIGHT; y++) {
		for (int x = 0; x < BOARDWIDTH; x++) {
			SDL_RenderCopy(renderer, board.getImageFromMap(x, y), NULL, board.getRectangle(x, y));
		}
	}

	SDL_RenderCopyEx(renderer, drow->getTexture(), drow->getSpriteRect(WayType::DOWN), drow->getPositionRect(), 0, NULL, SDL_FLIP_NONE);

	//Update screen
	SDL_RenderPresent(renderer);

}


bool init() {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
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
			}
		}
	}

	return true;
}

bool loadMedia(Character* drow) {
	//Loading success flag
	bool success = true;

	if (!board.loadImages(renderer)) {
		printf("Could not load Map;");
		return false;
	}


	if (!drow->loadImage(renderer)) {
		printf("Could not load drow;");
		return false;
	}

	drow->setNewPosition(32, 32);


	return success;
}

void close() {
	//Free loaded image
	//SDL_DestroyTexture(gTexture);
	//gTexture = NULL;

	board.~Board();

	//Destroy window    
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}