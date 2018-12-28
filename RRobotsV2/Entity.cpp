#include "Entity.h"



Entity::Entity(std::string filepath)
{
	this->filepath = filepath;
	this->tex = NULL;
}

Entity::Entity(std::string filepath, int width, int height)
{
	this->filepath = filepath;
	this->tex = NULL;
	position.w = width;
	position.h = height;
}

void Entity::setMapX(int x)
{
	mapX = x;
}

void Entity::setMapY(int y)
{
	mapY = y;
}

SDL_Rect * Entity::getPositionRect()
{
	return &position;
}

SDL_Texture * Entity::getTexture()
{
	return tex;
}

int Entity::getMapXPos()
{
	return mapX;
}

int Entity::getMapYPos()
{
	return mapY;
}

void Entity::setNewPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}


Entity::~Entity()
{
	SDL_DestroyTexture(tex);
	tex = NULL;
	filepath = "";
}

