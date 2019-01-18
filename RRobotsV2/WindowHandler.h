#pragma once
#ifdef _WIN32
#include <SDL_image.h>
#endif
#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#endif
#ifdef __linux__
#include <SDL2/SDL_image.h>
#endif
#include "Options.h"
class WindowHandler
{
public:
	WindowHandler();
	bool initWindowHandler(SDL_Window* window, Options* options, SDL_Renderer* renderer);
	bool setResolution(int w, int h);
	void switchFullscreen(bool fullscreen);
	void clearScreen();
	SDL_Window* getWindow();
	void getWindowSize(int* width, int* height);
	~WindowHandler();
private:
	SDL_Renderer* renderer;
	SDL_Window* window;
	Options* options;
	int currentScreenHeight;
	int currentScreenWidth;
};
