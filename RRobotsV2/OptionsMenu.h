#pragma once
#ifdef _WIN32
#include <SDL_image.h>
#endif
#ifdef __APPLE__ 
#include <SDL2_image/SDL2_image.h>
#endif
#ifdef __linux__
#include <SDL2/SDL_image.h>
#endif
#include "State.h"
#include "Options.h"
#include "AudioHandler.h"
#include "MusicHandler.h"
#include "WindowHandler.h"
#include "Gametext.h"
class OptionsMenu
{
public:
	OptionsMenu();
	bool init(SDL_Renderer* renderer, Options* options, WindowHandler* windowHandler, AudioHandler* audioHandler, MusicHandler* musicHandler);
	bool isInitialized();
	State logic();
	void draw(SDL_Renderer* renderer);

	~OptionsMenu();

private:
	SDL_Event e;
	Options* options;
	WindowHandler* windowHandler;
	AudioHandler* audioHandler;
	MusicHandler* musicHandler;
	std::vector<Gametext> optionMenues;
	std::vector<Gametext> changeMenuesValues;
};

