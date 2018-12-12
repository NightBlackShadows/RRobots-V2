#pragma once
#ifdef _WIN32
#include <SDL_image.h>
#endif
#if defined __APPLE__ | defined __LINUX__
#include <SDL2/SDL_image.h>
#endif
#include "TileType.h"
#include <vector>

#define BOARDWIDTH 18
#define BOARDHEIGHT 18

class Board
{
public:
	Board();
	bool loadImages(SDL_Renderer* renderer);
	std::vector< std::vector<int> > getGameBoard();
	std::vector< std::vector<int> > getEntityBoard();
	SDL_Texture* getImageFromMap(int x, int y);
	SDL_Rect* getRectangle(int x, int y);

	void setGameBoard(std::vector< std::vector<int> > Board);
	void setEntityBoard(std::vector< std::vector<int> > Board);

	std::string toString();
	~Board();

private:
	std::vector< std::vector<int> > gameBoard;
	std::vector< std::vector<int> > entityBoard;

	SDL_Rect rectangle;

	/*
	kan vara v�rt att byta ut SDL_Texture gameb.... mot en std::vector<SDL_Texture> 
	i st�llet s� beh�ver man inte begr�nsa sig till hur m�nga man skrivit h�r.
	kan man bara l�sa av hur m�nga som finns i mappen resources/Map/*

	kan man bara k�ra gameboardTexList.pushback();
	*/
	// Laddar in bilder i minnet
	SDL_Texture *GameBoard_brick;
	SDL_Texture *GameBoard_empty;
	SDL_Texture *GameBoard_up;
	SDL_Texture *GameBoard_left;
	SDL_Texture *GameBoard_TopRight;
	SDL_Texture *GameBoard_TopLeft;
	SDL_Texture *GameBoard_ButtomRight;
	SDL_Texture *GameBoard_ButtomLeft;


};

