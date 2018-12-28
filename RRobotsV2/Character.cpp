#include "Character.h"
#include "LoadTextures.h"


Character::Character(std::string filepath) : Entity::Entity(filepath)
{
	marked = false;
}

Character::Character(std::string filepath, int columbs, int rows) : Entity::Entity(filepath)
{
	this->columbs = columbs;
	this->rows = rows;

	marked = false;
	frame = 0;
}

bool Character::defineImage(int columbs, int rows)
{
	this->columbs = columbs;
	this->rows = rows;

	int w, h;
	if (tex == NULL) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"Missing texture",
			"Texture for character not loaded",
			NULL);
		return false;
	}
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);

	widthPerSprite = w / columbs;
	heightPerSprite = h / rows;
	position.w = widthPerSprite;
	position.h = heightPerSprite;

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
	frame = 0;

	return true;
}



bool Character::loadImage(SDL_Renderer* renderer) {
	Entity::tex = LoadTextures::loadTexture(renderer, Entity::filepath);

	if (tex == NULL) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"Missing texture",
			"Texture for character not loaded",
			NULL);
		return false;
	}

	return true;
}

void Character::setColor(int color)
{
	this->color = static_cast<ColorType>(color);
}

bool Character::getMarked()
{
	return marked;
}

void Character::setMarked(bool marked)
{
	this->marked = marked;
}

SDL_Texture * Character::getTexture()
{
	return tex;
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
	return &position;
}

ColorType Character::getColor()
{
	return color;
}

bool Character::compare(Character other)
{
	SDL_Rect otherRect = *other.getPositionRect();
	return (position.y > otherRect.y);
}

void Character::resetSprite()
{
	marked = false;
}



Character::~Character()
{
	if (tex != NULL)
	{
		SDL_DestroyTexture(tex);
	}
	tex = NULL;
	filepath = "";
	sprites.clear();
}
