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
#include <vector>
#include "FileHandler.h"

class Options
{
public:
	Options();
	bool loadOptions();
	int getMusicVolume();
	int getSoundVolume();
	bool getMute();
	std::string getMuteString();
	int getWidth();
	int getHeight();
	int getFPSLock();
	bool getFullscreen();
	std::string getFullscreenString();
	void setResolution(int w, int h);
	void setMusicVolume(int volume);
	void setSoundVolume(int volume);
	void setMute(bool state);
	void setFullscreen(bool state);
	void setFPSLock(int lock);
	void saveOptions();
	~Options();
private:

	void loadValues(std::string key,std::string value);
	FileHandler fileHandler;
	std::string filename;
	int fpsLock;
	int screenWidth;
	int screenHeight;
	int musicVolume;
	int soundVolume;
	bool mute;
	bool fullscreen;
};

