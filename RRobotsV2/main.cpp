#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Board.h"


//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

SDL_Renderer* renderer = NULL;

bool init();
bool loadMedia();
void draw(Board board);
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
		Board board;
		std::vector<std::vector<int>> gBoard;
		std::cout << board.toString() << std::endl;
		gBoard = board.getGameBoard();


		//Load media
		if (!board.loadImages(renderer))
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
					draw(board);

					//User requests quit
					if (e.type == SDL_QUIT)
					{
						running = false;
					}

				}
			}
		}

		board.~Board();
	}

	

	//Free resources and close SDL
	close();

	return 0;
}

void draw(Board board) {

	//Vill man testa att skriva ut något på bilden så gör det här!

	//Clear screen
	//SDL_RenderClear(renderer);

	//Draws the map
	for (int y = 0; y < BOARDHEIGHT; y++) {
		for (int x = 0; x < BOARDWIDTH; x++) {
			SDL_RenderCopy(renderer, board.getImageFromMap(x, y), NULL, board.getRectangle(x, y));
		}
	}

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

bool loadMedia() {
	//Loading success flag
	bool success = true;

	//Load splash image
	gHelloWorld = IMG_Load("resources/Map/brickwall.png");
	if (gHelloWorld == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "resources/Map/brickwall.png", SDL_GetError());
		success = false;
	}

	return success;
}

void close() {
	//Free loaded image
	//SDL_DestroyTexture(gTexture);
	//gTexture = NULL;

	//Destroy window    
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}