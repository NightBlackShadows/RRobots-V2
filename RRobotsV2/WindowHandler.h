#pragma once
#ifdef _WIN32
#include <SDL_image.h>
#endif
#if defined __APPLE__ | defined __linux__
#include <SDL2/SDL_image.h>
#endif
class WindowHandler
{
public:
	WindowHandler();
	bool initWindowHandler(SDL_Window* window);
	bool setResolution(int w, int h);
	void setFullscreen(bool fullscreen);
	SDL_Window* getWindow();
	void getWindowSize(int* width, int* height);
	~WindowHandler();
private:
	SDL_Window* window;
	int currentScreenHeight;
	int currentScreenWidth;
};

