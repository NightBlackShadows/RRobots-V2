#pragma once
#ifdef _WIN32
#include <SDL_image.h>
#include <SDL_ttf.h>
#endif
#ifdef __APPLE__ 
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#endif
#ifdef __linux__
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif
#include <string>
class Gametext
{
public:
	Gametext(std::string text);
	bool init(std::string font, SDL_Renderer *renderer);
	void setTextRect(int x, int y, int width, int height);
	std::string getText();
	void setPos(int x, int y); 
	void setNewText(std::string newText);
	void setTextColor();
	void setRandTextColor();
	SDL_Rect* getPos();
	SDL_Texture* getTexture();
	void makeTexture();
	~Gametext();
private:
	std::string text;
	TTF_Font *font;
	SDL_Color Color;
	SDL_Rect Rect;
	SDL_Texture *tex;
	SDL_Surface *screenSurface;
	SDL_Renderer* renderer;
};

