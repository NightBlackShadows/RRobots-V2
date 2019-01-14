#include "Gametext.h"
#include <random>
#include <time.h>
#include <iostream>



Gametext::Gametext(std::string text)
{
	srand(time(NULL));
	this->text = text;

	Rect.x = 0;
	Rect.y = 0;
	Rect.w = 0;
	Rect.h = 0;
}

bool Gametext::init(std::string fontLocation)
{

	font = TTF_OpenFont(fontLocation.c_str(), 24);
	if (font == NULL)
	{
		SDL_assert(font == NULL);
		std::cout << SDL_GetError() << std::endl;
		return false;
	}


	return true;
}

void Gametext::setTextRect(int x, int y, int width, int height)
{
	Rect.x = x;
	Rect.y = y;
	Rect.w = width;
	Rect.h = height;
}

std::string Gametext::getText()
{
	return text;
}

void Gametext::setPos(int x, int y)
{
	Rect.x = x;
	Rect.y = y;
}

void Gametext::setTextColor()
{
	Color.r = 255;
	Color.g = 0;
	Color.b = 0;
}

void Gametext::setRandTextColor()
{
	int r = rand() % 155;
	int g = rand() % 155;
	int b = rand() % 155;
	Color.r = r + 100;
	Color.g = g + 100;
	Color.b = b + 100;
}
SDL_Rect * Gametext::getPos()
{
	return &Rect;
}
SDL_Texture* Gametext::getTexture()
{
	return tex;
}
void Gametext::makeTexture(SDL_Renderer *renderer)
{
	screenSurface = TTF_RenderText_Solid(font, text.c_str(), Color);
	tex = SDL_CreateTextureFromSurface(renderer, screenSurface);
	SDL_FreeSurface(screenSurface);
}
Gametext::~Gametext()
{
	text.clear();
	
}
