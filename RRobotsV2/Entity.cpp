#include "Entity.h"


//Constructor of an entity
Entity::Entity(std::string filepath)
{
	this->filepath = filepath;
	this->tex = NULL;
}

//Constructor of an entity with width and height of the image
Entity::Entity(std::string filepath, int width, int height)
{
	this->filepath = filepath;
	this->tex = NULL;
	position.w = width;
	position.h = height;
}

//Set the xpos of the enity
void Entity::setMapX(int x)
{
	mapX = x;
}

//Set the ypos of the entity
void Entity::setMapY(int y)
{
	mapY = y;
}

//Return the position of the entity
SDL_Rect * Entity::getPositionRect()
{
	return &position;
}

//Get the texture of the entity
SDL_Texture * Entity::getTexture()
{
	return tex;
}

//Get the map xpos of the entity
int Entity::getMapXPos()
{
	return mapX;
}

//get the map ypos of the entity
int Entity::getMapYPos()
{
	return mapY;
}

//Set a new position
void Entity::setNewPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

//Desturctor
Entity::~Entity()
{
	SDL_DestroyTexture(tex);
	tex = NULL;
	filepath = "";
}

