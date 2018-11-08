#include "Marker.h"
#include "LoadTextures.h"


/*
Used for having individual pictures for each marker
*/
Marker::Marker(std::string filepath) : Entity::Entity(filepath)
{
}

/*
Used for having a sprite as a marker with all possible alternatives
*/
Marker::Marker(std::string filepath, int widthPerSprite, int heightPerSprite, int columbs) : Entity::Entity(filepath,widthPerSprite,heightPerSprite)
{
	this->widthPerSprite = widthPerSprite;
	this->heightPerSprite = heightPerSprite;
	this->columbs = columbs;
}

bool Marker::loadImage(SDL_Renderer* renderer)
{
	Entity::tex = LoadTextures::loadTexture(renderer, Entity::filepath);

	if (tex == NULL) {
		return false;
	}

	return true;
}

bool Marker::defineImage(int columbs)
{
	this->columbs = columbs;
	int w, h;
	if (tex == NULL) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"Missing texture",
			"Texture for marker not loaded",
			NULL);
		return false;
	}
	else {
		SDL_QueryTexture(tex, NULL, NULL, &w, &h);
		position.w = w;
		position.h = h;
		if (columbs == 1) {
			return true;
		}
		else {
			widthPerSprite = w / columbs;
			position.w = widthPerSprite;
			heightPerSprite = h;

			for (int y = 0; y < 1; y++) {
				for (int x = 0; x < this->columbs; x++) {
					SDL_Rect rect;
					rect.w = widthPerSprite;
					rect.h = heightPerSprite;
					rect.x = widthPerSprite * x;
					rect.y = heightPerSprite * y;
					sprites.push_back(rect);
				}
			}
		}
	}
	return true;
}



SDL_Rect * Marker::getSpriteRect(ColorType color)
{
	switch (color) {
	case ColorType::GREEN:
		return &sprites.at(0);
	case ColorType::BLUE:
		return &sprites.at(1);
	case ColorType::BLACK:
		return &sprites.at(2);
	case ColorType::RED:
		return &sprites.at(3);
	case ColorType::YELLOW:
		return &sprites.at(4);
	default:
		return &sprites.at(5);
	}
	return nullptr;
}

void Marker::setColor(ColorType newColor)
{
	color = newColor;
}

ColorType Marker::getColor()
{
	return color;
}


Marker::~Marker()
{
	Entity::~Entity();
	sprites.clear();
}
