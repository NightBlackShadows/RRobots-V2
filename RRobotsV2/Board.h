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
	kan vara värt att byta ut SDL_Texture gameb.... mot en std::vector<SDL_Texture> 
	i stället så behöver man inte begränsa sig till hur många man skrivit här.
	kan man bara läsa av hur många som finns i mappen resources/Map/*

	kan man bara köra gameboardTexList.pushback();
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

