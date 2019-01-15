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
#include "Gametext.h"
class OptionsMenu
{
public:
	OptionsMenu(Options* options);
	bool init(SDL_Renderer* renderer);
	bool isInitialized();
	State logic();
	void draw(SDL_Renderer* renderer);

	~OptionsMenu();

private:
	SDL_Event e;
	Options* options;
	std::vector<Gametext> menues;
};

