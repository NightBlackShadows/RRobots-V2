#pragma once
#ifdef _WIN32
#include <SDL_image.h>
#endif
#if defined __APPLE__ | defined __linux__
#include <SDL2/SDL_image.h>
#endif
#include <string>

class LoadTextures
{
public:
	static SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string filepath);
private:
	LoadTextures();	
	~LoadTextures();
};

