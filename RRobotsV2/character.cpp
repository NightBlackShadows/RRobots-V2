#include "Character.h"
#include "LoadTextures.h"


Character::Character(std::string filepath, int widthPerSprite, int heightPerSprite, int columbs, int rows) : Entity::Entity(filepath, widthPerSprite, heightPerSprite)
{
	this->widthPerSprite = widthPerSprite;
	this->heightPerSprite = heightPerSprite;
	this->columbs = columbs;
	this->rows = rows;

	moving = false;
	frame = 0;
}

bool Character::loadImage(SDL_Renderer* renderer) {
	Entity::tex = LoadTextures::loadTexture(renderer, Entity::filepath);

	if (tex == NULL) {
		return false;
	}

	for (int y = 0; y < this->rows; y++) {
		for (int x = 0; x < this->columbs; x++) {
			SDL_Rect rect;
			rect.w = widthPerSprite;
			rect.h = heightPerSprite;
			rect.x = widthPerSprite * x;
			rect.y = heightPerSprite * y;
			sprites.push_back(rect);
		}
	}
	return true;
}

SDL_Texture * Character::getTexture()
{
	return Entity::getTexture();
}

SDL_Rect * Character::getSpriteRect(WayType wayType)
{
	switch (wayType) {
	case WayType::DOWN:
		if (frame < columbs-1) {
			frame++;
			return &sprites[frame];
		}
		else {
			frame = 0;
			return &sprites[frame];
		}
	case WayType::LEFT:
		if (frame >= columbs && frame < columbs*2 - 1) {
			frame++;
			return &sprites[frame];
		}
		else {
			frame = columbs;
			return &sprites[frame];
		}
	case WayType::RIGHT:
		if (frame >= columbs*2 && frame < columbs*3 - 1) {
			frame++;
			return &sprites[frame];
		}
		else {
			frame = columbs*2;
			return &sprites[frame];
		}
	case WayType::UP:
		if (frame >= columbs*3 && frame < columbs*4-1) {
			frame++;
			return &sprites[frame];
		}
		else {
			frame = columbs*3;
			return &sprites[frame];
		}
	default:
		return &sprites[0];
	}
}

SDL_Rect * Character::getPositionRect()
{
	return Entity::getPositionRect();
}



void Character::resetSprite()
{
	moving = false;
}



Character::~Character()
{
	Entity::~Entity();
	sprites.clear();
}
