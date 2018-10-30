#include "Board.h"
#include "LoadTextures.h"
#include <string>


Board::Board()
{
	//gameBoard = new std::vector< std::vector<TileType> >(BOARDHEIGHT, std::vector<TileType>(BOARDWIDTH));
	std::vector< std::vector<int> > gBoard{
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },			//0 Ingen ruta
	{ 0,1,1,1,1,3,1,1,1,1,1,1,1,3,1,1,1,0 },			//1 Utan vägg
	{ 0,1,1,1,1,1,1,6,1,1,1,1,1,1,1,1,1,0 },			//2 EN vägg UPPE 
	{ 0,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,1,0 },			//3 EN vägg till VÄNSTER
	{ 0,1,4,1,1,1,1,1,1,1,1,1,1,1,4,1,1,0 },			//4 HÖRN UPPE till HÖGER 
	{ 0,1,1,1,1,1,5,1,1,1,1,6,1,1,1,1,1,0 },			//5 HÖRN UPPE till VÄNSTER
	{ 0,1,1,7,1,1,1,1,7,1,1,1,1,5,1,1,1,0 },			//6 HÖRN NERE till VÄNSTER 
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,0 },			//7 HÖRN NERE till HÖGER
	{ 0,2,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,6,1,1,1,2,0 },
	{ 0,1,1,1,1,1,6,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,1,5,1,1,1,1,1,1,1,1,1,1,1,1,4,1,0 },
	{ 0,1,1,1,1,1,1,4,1,1,5,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,2,1,1,7,1,1,1,1,1,1,1,1,7,1,1,1,0 },
	{ 0,1,1,1,1,1,1,3,1,1,1,1,1,1,1,3,1,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	};

	std::vector< std::vector<int> > eBoard	{
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },			//0 Ingen gubbe
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },			//1 Ingen Tile
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },			//2 Link
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },			//3 Sonic
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },			//4 Stormtrooper
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },			//5 Pikmin
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },			//6 marle
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },			//7 Active token is randomized
	{ 1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	};

	gameBoard = gBoard;
	entityBoard = eBoard;
}



Board::~Board()
{
	//Free loaded image
	SDL_DestroyTexture(GameBoard_brick);
	GameBoard_brick = NULL;
	SDL_DestroyTexture(GameBoard_empty);
	GameBoard_empty = NULL;
	SDL_DestroyTexture(GameBoard_up);
	GameBoard_up = NULL;
	SDL_DestroyTexture(GameBoard_left);
	GameBoard_left = NULL;
	SDL_DestroyTexture(GameBoard_TopRight);
	GameBoard_TopRight = NULL;
	SDL_DestroyTexture(GameBoard_TopLeft);
	GameBoard_TopLeft = NULL;
	SDL_DestroyTexture(GameBoard_ButtomRight);
	GameBoard_ButtomRight = NULL;
	SDL_DestroyTexture(GameBoard_ButtomLeft);
	GameBoard_ButtomLeft = NULL;
}

std::vector< std::vector<int> > Board::getGameBoard()
{
	return Board::gameBoard;
}

std::vector< std::vector<int> > Board::getEntityBoard()
{
	return Board::entityBoard;
}

void Board::setGameBoard(std::vector< std::vector<int> > Board)
{
	for (int y = 1; y < BOARDHEIGHT; y++) {
		for (int x = 1; x < BOARDWIDTH; x++) {
			gameBoard[y][x] = Board[y][x];
		}
	}
}

void Board::setEntityBoard(std::vector< std::vector<int> > board)
{
	for (int y = 1; y < BOARDHEIGHT -1; y++) {
		for (int x = 1; x < BOARDWIDTH -1; x++) {
			entityBoard[y][x] = board[y][x];
		}
	}
}



SDL_Texture* Board::getImageFromMap(int x, int y)
{
	switch (gameBoard[y][x]) {
	case 0:
		return GameBoard_brick;
	case 1:
		return GameBoard_empty;
	case 2:
		return GameBoard_up;
	case 3:
		return GameBoard_left;
	case 4:
		return GameBoard_TopRight;
	case 5:
		return GameBoard_TopLeft;
	case 6:
		return GameBoard_ButtomLeft;
	case 7:
		return GameBoard_ButtomRight;
	default:
		return GameBoard_brick;
	}
}

SDL_Rect* Board::getRectangle(int x, int y)
{
	rectangle.w = 32;
	rectangle.h = 32;
	rectangle.y = y * 32;
	rectangle.x = x * 32;

	return &rectangle;
}

bool Board::loadImages(SDL_Renderer* renderer)
{
	//Load splash image
	GameBoard_brick = LoadTextures::loadTexture(renderer,"resources/Map/brickwall.png");
	GameBoard_empty = LoadTextures::loadTexture(renderer, "resources/Map/TomGimpRuta.png");
	GameBoard_up = LoadTextures::loadTexture(renderer, "resources/Map/SingleGimpRutaUp.png");
	GameBoard_left = LoadTextures::loadTexture(renderer, "resources/Map/SingleGimpRutaLeft.png");
	GameBoard_TopRight = LoadTextures::loadTexture(renderer, "resources/Map/CornerGimpRutaTR.png");
	GameBoard_TopLeft = LoadTextures::loadTexture(renderer, "resources/Map/CornerGimpRutaTL.png");
	GameBoard_ButtomRight = LoadTextures::loadTexture(renderer, "resources/Map/CornerGimpRutaBR.png");
	GameBoard_ButtomLeft = LoadTextures::loadTexture(renderer, "resources/Map/CornerGimpRutaBL.png");

	if (GameBoard_brick == NULL) {
		return false;
	}
	if (GameBoard_brick == NULL) {
		return false;
	}
	if (GameBoard_brick == NULL) {
		return false;
	}
	if (GameBoard_brick == NULL) {
		return false;
	}
	if (GameBoard_brick == NULL) {
		return false;
	}
	if (GameBoard_brick == NULL) {
		return false;
	}
	if (GameBoard_brick == NULL) {
		return false;
	}
	if (GameBoard_brick == NULL) {
		return false;
	}
	if (GameBoard_brick == NULL) {
		return false;
	}
	if (GameBoard_brick == NULL) {
		return false;
	}



	return true;
}

std::string Board::toString() {
	std::string buffer;

	for (int y = 0; y < BOARDHEIGHT; y++) {
		buffer += "[ ";
		for (int x = 0; x < BOARDWIDTH; x++) {
			buffer += std::to_string(gameBoard[y][x]);
			buffer += ", ";
		}
		buffer += "]\n";
	}
	
	return buffer;
}