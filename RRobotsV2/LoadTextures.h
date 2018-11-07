#pragma once
#ifdef _WIN32
#include <SDL_image.h>
#endif
#if defined __APPLE__ | defined __LINUX__
#include <SDL2_image/SDL_image.h>
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

