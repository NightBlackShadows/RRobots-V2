#pragma once
#include <SDL_image.h>
#include <vector>
#include "entity.h"
#include "WayType.h"

class Character :
	public Entity
{
public:
	Character(std::string filepath, int widthPerSprite, int heightPerSprite, int columbs, int rows);
	bool loadImage(SDL_Renderer* renderer);
	SDL_Texture* getTexture();
	SDL_Rect* getSpriteRect(WayType wayType);
	SDL_Rect* getPositionRect();
	void resetSprite();
	~Character();

private:
	std::vector<SDL_Rect> sprites;
	bool moving;
	int frame;
	int widthPerSprite;
	int heightPerSprite;
	int columbs;
	int rows;
};

