#include "WindowHandler.h"



WindowHandler::WindowHandler()
{
}

//Initialize display window
bool WindowHandler::initWindowHandler(SDL_Window * window, Options* options, SDL_Renderer* renderer)
{
	this->window = window;
	this->options = options;
	this->renderer = renderer;
	return false;
}

//Set resolution
bool WindowHandler::setResolution(int w, int h)
{

	if (w > 0 && h > 0) {
		options->setResolution(w, h);
		SDL_SetWindowSize(window, w, h);
	}
	else {
		return false;
	}

	return true;
}

//Switch fullscreen
void WindowHandler::switchFullscreen(bool fullscreen)
{
	options->setFullscreen(fullscreen);
	if (fullscreen == true) {
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	}
	else {
		SDL_SetWindowFullscreen(window, NULL);
	}
}

//Get current display window
SDL_Window * WindowHandler::getWindow()
{
	return window;
}

//Get current resolution of window
void WindowHandler::getWindowSize(int * width, int * height)
{
	SDL_GetWindowSize(window, width, height);
}

void WindowHandler::clearScreen(){
	SDL_RenderClear(renderer);
}

WindowHandler::~WindowHandler()
{
}
