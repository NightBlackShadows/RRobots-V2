#include "GameLogic.h"
#include "WayType.h"
#include <stdlib.h>
#include <time.h>

struct tile_pos
{
	int x;
	int y;
	int posNr;
	int type;
}; typedef struct tile_pos TilePos;


GameLogic::GameLogic()
{
	srand(time(NULL));
}

void GameLogic::randomizeCharacterPos(std::vector<Character>* characters)
{
	int x, y;
	for (int chars = 0; chars < characters->size(); chars++) {
		do
		{
			x = rand() % 16 + 1;
			y = rand() % 16 + 1;
		} while (entityBoard[y][x] != 0);
		entityBoard[y][x] = chars;
		characters->at(chars).setNewPosition(32 * x, 32 * y - 32);
	}
}

void GameLogic::randomizeMarker(std::vector<Marker>* markers)
{
	TilePos tilePos[50];

	for (int i = 0; i < 50; i++)
	{
		tilePos[i].x = 0;
		tilePos[i].y = 0;
		tilePos[i].posNr = 0;
	}

	int tokenPosX = 1, tokenPosY = 1, nrOfPlaces = 0;
	for (int y = 2; y < BOARDHEIGHT - 2; y++)
	{
		for (int x = 2; x < BOARDWIDTH - 2; x++)
		{
			if (entityBoard.at(y).at(x) == 7)
			{
				entityBoard[y][x] = 0;
			}
			if (gameBoard[y][x] > 3)
			{
				tilePos[nrOfPlaces].x = x;
				tilePos[nrOfPlaces].y = y;
				tilePos[nrOfPlaces].posNr = (nrOfPlaces + 1);
				nrOfPlaces++;
			}
		}
	}
	int i;

	do
	{
		i = rand() % 16;
		tokenPosX = tilePos[i].x;
		tokenPosY = tilePos[i].y;
	} while (entityBoard[tokenPosY][tokenPosX] != 0);
	entityBoard[tokenPosY][tokenPosX] = 7;

	currentMarker = static_cast<ColorType>(rand() % 5);
	for (int i = 0; i < markers->size(); i++) {
		markers->at(i).setNewPosition(32 * tokenPosX + (32*0.19),32 * tokenPosY + (32 * 0.19));
	}
}

ColorType GameLogic::getCurrentMarker()
{
	return currentMarker;
}

void GameLogic::setGameBoard(std::vector<std::vector<int>> gameBoard)
{
	this->gameBoard = gameBoard;
}

void GameLogic::setEntityBoard(std::vector<std::vector<int>> entityBoard)
{
	this->entityBoard = entityBoard;
}


/*
måste fixas till! PROTOTYP
*/
bool GameLogic::detectCollision(SDL_Rect character, SDL_Rect marker, WayType way)
{
	switch (way) {
	case WayType::LEFT:
		if (character.x <= marker.x && character.y <= marker.y) {
			return true;
		}
	case WayType::RIGHT:
		if (character.x >= marker.x && character.y >= marker.y) {
			return true;
		}
	case WayType::UP:
	case WayType::DOWN:
	default:
		return false;
	}
}

GameLogic::~GameLogic()
{
}
