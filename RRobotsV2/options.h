#pragma once

#ifdef _WIN32
#include <SDL_image.h>
#endif
#if defined __APPLE__ | defined __LINUX__
#include <SDL2_image/SDL_image.h>
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
	bool getFullscreen();
	void saveOptions();
	~Options();
private:
	void loadValues(std::string key,std::string value);
	FileHandler fileHandler;
	std::string filename;
	int screenWidth;
	int screenHeight;
	int volume;
	bool mute;
	bool fullscreen;
};

