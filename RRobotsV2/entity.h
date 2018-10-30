#pragma once
#include <SDL_image.h>
#include <string>
class Entity
{
public:
	Entity(std::string filepath, int width, int height);
	SDL_Rect* getPositionRect();
	SDL_Texture* getTexture();
	void setNewPosition(int x, int y);
	virtual ~Entity();
protected:
	std::string filepath;
	SDL_Texture* tex;
	SDL_Rect position;
};

