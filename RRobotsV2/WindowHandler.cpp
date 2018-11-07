#include "WindowHandler.h"



WindowHandler::WindowHandler()
{
}


bool WindowHandler::initWindowHandler(SDL_Window * window)
{
	this->window = window;

	return false;
}

bool WindowHandler::setResolution(int w, int h)
{

	if (w > 0 && h > 0) {
		currentScreenHeight = h;
		currentScreenWidth = w;
		SDL_SetWindowSize(window, w, h);
	}
	else {
		return false;
	}

	return true;
}

void WindowHandler::setFullscreen(bool fullscreen)
{
	if (fullscreen == true) {
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	}
	else {
		SDL_SetWindowFullscreen(window, NULL);
	}
}

SDL_Window * WindowHandler::getWindow()
{
	return window;
}

void WindowHandler::getWindowSize(int * width, int * height)
{
	SDL_GetWindowSize(window, width, height);
}



WindowHandler::~WindowHandler()
{
}
