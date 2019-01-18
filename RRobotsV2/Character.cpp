#include "Character.h"
#include "LoadTextures.h"

//Constructor of a character entity
Character::Character(std::string filepath) : Entity::Entity(filepath)
{
	marked = false;
}

//Constructor for a character entity that is a sprite
Character::Character(std::string filepath, int columbs, int rows) : Entity::Entity(filepath)
{
	this->columbs = columbs;
	this->rows = rows;

	marked = false;
	frame = 0;
}

//Define how many rows and columns the sprite is
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

//Load a image for the entity
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

//Set the "marker" color for the entity
void Character::setColor(int color)
{
	this->color = static_cast<ColorType>(color);
}

//Check if character is marked
bool Character::getMarked()
{
	return marked;
}

//Set the character to marked
void Character::setMarked(bool marked)
{
	this->marked = marked;
}

//Get the texture of the character
SDL_Texture * Character::getTexture()
{
	return tex;
}

//Get the sprite rectangle of the character
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

//Get the current position of the character
SDL_Rect * Character::getPositionRect()
{
	return &position;
}

//Get the color of the character
ColorType Character::getColor()
{
	return color;
}

//Compere the position between two characters
bool Character::compare(Character other)
{
	SDL_Rect otherRect = *other.getPositionRect();
	return (position.y > otherRect.y);
}

//Reset the marked status
void Character::resetSprite()
{
	marked = false;
}

//Destructor
Character::~Character()
{
	/*if (tex != NULL)
	{
		SDL_DestroyTexture(tex);
	}*/
	//tex = NULL;
	//filepath = "";
	//sprites.clear();
}
