#pragma once
#include <SDL_image.h>
#include "TileType.h"
#include <vector>

#define BOARDWIDTH 18
#define BOARDHEIGHT 18

class Board
{
public:
	Board();
	~Board();
	std::vector< std::vector<int> > getGameBoard();
	std::vector< std::vector<int> > getEntityBoard();

	void setGameBoard(std::vector< std::vector<int> > Board);
	void setEntityBoard(std::vector< std::vector<int> > Board);

	SDL_Texture* getImageFromMap(int x,int y);
	SDL_Rect* getRectangle(int x, int y);
	bool loadImages(SDL_Renderer* renderer);

	std::string toString();

private:
	std::vector< std::vector<int> > gameBoard;
	std::vector< std::vector<int> > entityBoard;


	SDL_Rect rectangle;
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

