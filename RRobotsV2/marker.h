#pragma once
#include "Entity.h"
#include "ColorType.h"
#include <vector>
class Marker :
	public Entity
{
public:
	Marker(std::string filepath);
	Marker(std::string filepath, int widthPerSprite, int heightPerSprite, int columbs);
	bool loadImage(SDL_Renderer* renderer);
	bool defineImage(int columbs);
	SDL_Rect* getSpriteRect(ColorType color);
	void setColor(ColorType newColor);
	ColorType getColor();

	~Marker();

private:
	std::vector<SDL_Rect> sprites;
	ColorType color;
	int widthPerSprite;
	int heightPerSprite;
	int columbs;
};

