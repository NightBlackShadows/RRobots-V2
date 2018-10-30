#pragma once
#include <SDL_image.h>
#include <string>

class LoadTextures
{
public:
	static SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string filepath);
private:
	LoadTextures();	
	~LoadTextures();
};

