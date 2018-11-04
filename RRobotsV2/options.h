#pragma once
#include <SDL_image.h>
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

