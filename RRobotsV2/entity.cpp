#include "entity.h"



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

SDL_Rect * Entity::getPositionRect()
{
	return &position;
}

SDL_Texture * Entity::getTexture()
{
	return tex;
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

