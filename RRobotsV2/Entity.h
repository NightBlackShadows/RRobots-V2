#pragma once
#ifdef _WIN32
#include <SDL_image.h>
#endif
#if defined __APPLE__ | defined __LINUX__
#include <SDL2_image/SDL_image.h>
#endif
#include <string>
class Entity
{
public:
	Entity(std::string filepath);
	Entity(std::string filepath, int width, int height);
	void setMapX(int x);
	void setMapY(int y);
	SDL_Rect* getPositionRect();
	SDL_Texture* getTexture();
	int getMapXPos();
	int getMapYPos();
	void setNewPosition(int x, int y);
	virtual ~Entity();
protected:
	int mapX;
	int mapY;
	std::string filepath;
	SDL_Texture* tex;
	SDL_Rect position;
};
