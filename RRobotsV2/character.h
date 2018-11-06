#pragma once
#include <SDL_image.h>
#include <vector>
#include "entity.h"
#include "WayType.h"
#include "ColorType.h"

class Character :
	public Entity
{
public:
	Character(std::string filepath);
	Character(std::string filepath, int columbs, int rows);
	bool defineImage(int columbs, int rows);
	bool loadImage(SDL_Renderer* renderer);
	void setColor(int color);
	bool getMarked();
	void setMarked(bool marked);
	SDL_Texture* getTexture();
	SDL_Rect* getSpriteRect(WayType wayType);
	SDL_Rect* getPositionRect();
	ColorType getColor();
	bool compare(Character other);
	void resetSprite();
	~Character();

private:
	std::vector<SDL_Rect> sprites;
	bool marked;
	ColorType color;
	int frame;
	int widthPerSprite;
	int heightPerSprite;
	int columbs;
	int rows;
};

