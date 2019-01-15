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
#include <vector>
#include "State.h"
#include "Gametext.h"
#include "Options.h"
class MainMenu
{
public:
	MainMenu();
	bool init(SDL_Renderer *renderer, Options* options);
	bool isInitialized();
	State logic();
	void draw(SDL_Renderer* renderer);
	~MainMenu();
private:
	SDL_Event e;
	Options* options;
	std::vector<Gametext> menues;
};

