#pragma once

#ifdef _WIN32
#include <SDL_image.h>
#endif
#ifdef __APPLE__
#include "SDL2_image/SDL_image.h"
#endif
#ifdef __linux__
#include <SDL2/SDL_image.h>
#endif
#include "FileHandler.h"
class Options
{
public:
	Options();
	bool loadOptions();
	int getVolume();
	bool getMute();
	int getWidth();
	int getHeight();
	int getFPSLock();
	bool getFullscreen();
	void saveOptions();
	~Options();
private:
	void loadValues(std::string key,std::string value);
	FileHandler fileHandler;
	std::string filename;
	int fpsLock;
	int screenWidth;
	int screenHeight;
	int volume;
	bool mute;
	bool fullscreen;
};

