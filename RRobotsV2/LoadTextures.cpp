#include "LoadTextures.h"



LoadTextures::LoadTextures()
{
}


LoadTextures::~LoadTextures()
{
}

SDL_Texture* LoadTextures::loadTexture(SDL_Renderer* renderer, std::string filepath) {
	SDL_Texture* newTexture = NULL;
	SDL_Surface* surface = IMG_Load(filepath.c_str());
	
	if (surface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", filepath.c_str(), IMG_GetError());
	}
	else {
		newTexture = SDL_CreateTextureFromSurface(renderer, surface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", filepath.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(surface);
	}

	return newTexture;
}