#pragma once
#ifdef _WIN32
#include <SDL_image.h>
#endif
#ifdef __APPLE__ 
#endif
#ifdef __linux__ 
#include <SDL2/SDL_image.h>
#endif
#include <vector>
#include "Entity.h"
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

