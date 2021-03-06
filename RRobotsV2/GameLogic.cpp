#include "GameLogic.h"
#include "WayType.h"
#include <stdlib.h>
#include <time.h>
#include <string>

struct tile_pos
{
	int x;
	int y;
	int posNr;
	int type;
}; typedef struct tile_pos TilePos;

//Constructor and start a randomizer
GameLogic::GameLogic()
{
	srand((unsigned)time(NULL));
}

//Randomize position of the characters
void GameLogic::randomizeCharacterPos(std::vector<Character>* characters)
{
	int x, y;
	for (int chars = 0; chars < (int)characters->size(); chars++) {
		do
		{
			x = rand() % 16 + 1;
			y = rand() % 16 + 1;
		} while (entityBoard[y][x] != 0);
		entityBoard[y][x] = chars+2;
		characters->at(chars).setMapX(x);
		characters->at(chars).setMapY(y);
		characters->at(chars).setNewPosition(32 * x, 32 * y - 32);
	}
}

//Randomize the markers position
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
	markers->at(0).setColor(currentMarker);
	for (int i = 0; i < (int)markers->size(); i++) {
		markers->at(i).setMapX(tokenPosX);
		markers->at(i).setMapY(tokenPosY);
		markers->at(i).setNewPosition(32 * tokenPosX + (int)(32*0.19),32 * tokenPosY + (int)(32 * 0.19));
	}
}

//Change current marked character
int GameLogic::changeMarked(std::vector<Character> &characters) {
	int x = 0;
	for (int i = 0; i < (int)characters.size(); i++) {
		if (characters[i].getMarked()) {
			characters[i].setMarked(false);
			if (i == characters.size() - 1) {
				characters[0].setMarked(true);
				x = 0;
			}
			else {
				characters[i + 1].setMarked(true);
				x = i + 1;
			}
			i = characters.size();
		}
		if (i == (int)characters.size() - 1) {
			characters[0].setMarked(true);

		}
	}
	return x;
}

//Get entity board
std::vector<std::vector<int>> GameLogic::getEntityBoard()
{
	return entityBoard;
}

//Get what character is marked
ColorType GameLogic::getCurrentMarker()
{
	return currentMarker;
}

//Set what gameboard shall be shown
void GameLogic::setGameBoard(std::vector<std::vector<int>> gameBoard)
{
	this->gameBoard = gameBoard;
}

//Set entity board (Character posistions)
void GameLogic::setEntityBoard(std::vector<std::vector<int>> entityBoard)
{
	this->entityBoard = entityBoard;
}

//Reset entity board
void GameLogic::resetEntityBoard(std::vector<Character> &characters)
{
	entityBoard = orgEntityBoard;
	for (int y = 0; y < BOARDHEIGHT; y++) {
		for (int x = 0; x < BOARDWIDTH; x++) {

		}
	}
}

//Move a character
bool GameLogic::moveCharacter(Character &character,SDL_Rect dest)
{
	SDL_Rect charPos = *character.getPositionRect();
	int newX, newY;
	newX = charPos.x;
	newY = charPos.y;
	if (dest.x > charPos.x) {
		newX += 2;
	}
	else if (dest.y > charPos.y) {
		newY += 2;
	}
	else if (dest.x < charPos.x) {
		newX -= 2;
	}
	else if (dest.y < charPos.y) {
		newY -= 2;
	}
	if (dest.x >= 0 && dest.y >= 0) {
		if (dest.x == charPos.x && dest.y == charPos.y) {
			return false;
		}

		character.setNewPosition(newX, newY);
	}
	return true;
}

//Check if the correct character collides with the marker
bool GameLogic::markerCollision(Character &character, Marker &marker)
{
	if (character.getMapXPos() == marker.getMapXPos() &&
		character.getMapYPos() == marker.getMapYPos()) {
		if (character.getColor() == marker.getColor()) {
			return true;
		}
	}
	return false;
}

//Detect collision of characters and walls
SDL_Rect GameLogic::detectCollision(Character &character, SDL_Rect marker, WayType way)
{
	int x, y;
	y = character.getMapYPos();
	x = character.getMapXPos();
	SDL_Rect newPos;
	switch (way) {
	case WayType::LEFT:
		while ( x > 1) {
			if (gameBoard[y][x - 1] == 0 ||	gameBoard[y][x - 0] == 3 ||
				gameBoard[y][x - 1] == 4 ||	gameBoard[y][x - 0] == 5 ||
				gameBoard[y][x - 0] == 6 ||	gameBoard[y][x - 1] == 7 ||
				(entityBoard[y][x - 1] >= 2 && entityBoard[y][x - 1] <= 6))
			{
				if (x != character.getMapXPos() || y != character.getMapYPos()) {
					entityBoard[y][x] = entityBoard[character.getMapYPos()][character.getMapXPos()];
					entityBoard[character.getMapYPos()][character.getMapXPos()] = 0;
					character.setMapX(x);
				}
				newPos.x = x * 32;
				newPos.y = y * 32 - 32;
				return newPos;
			}
			else {
			}
			x--;
			if (x <= 1) {
				entityBoard[y][x] = entityBoard[character.getMapYPos()][character.getMapXPos()];
				entityBoard[character.getMapYPos()][character.getMapXPos()] = 0;
				character.setMapX(x);
			}
		}
		newPos.x = x * 32;
		newPos.y = y * 32 - 32;
		return newPos;
	case WayType::RIGHT:
		while (x < 16) {
			if (gameBoard[y][x + 1] == 0 || gameBoard[y][x + 1] == 3 ||
				gameBoard[y][x + 0] == 4 || gameBoard[y][x + 1] == 5 ||
				gameBoard[y][x + 1] == 6 || gameBoard[y][x + 0] == 7 ||
				(entityBoard[y][x + 1] >= 2 && entityBoard[y][x + 1] <= 6))
			{
				if (x != character.getMapXPos() || y != character.getMapYPos()) {
					entityBoard[y][x] = entityBoard[character.getMapYPos()][character.getMapXPos()];
					entityBoard[character.getMapYPos()][character.getMapXPos()] = 0;
					character.setMapX(x);
				}
				newPos.x = x * 32;
				newPos.y = y * 32 - 32;
				return newPos;
			}
			else {
			}
			x++;
			if (x >= 16) {
				entityBoard[y][x] = entityBoard[character.getMapYPos()][character.getMapXPos()];
				entityBoard[character.getMapYPos()][character.getMapXPos()] = 0;
				character.setMapX(x);
			}
		}
		newPos.x = x * 32;
		newPos.y = y * 32 - 32;
		return newPos;
	case WayType::UP:
		while (y > 1) {
			if (gameBoard[y - 1][x] == 0 ||	gameBoard[y + 0][x] == 2 ||
				gameBoard[y + 0][x] == 4 ||	gameBoard[y + 0][x] == 5 ||
				gameBoard[y - 1][x] == 6 ||	gameBoard[y - 1][x] == 7 ||
				(entityBoard[y - 1][x] >= 2 && entityBoard[y - 1][x] <= 6))
			{
				if (x != character.getMapXPos() || y != character.getMapYPos()) {
					entityBoard[y][x] = entityBoard[character.getMapYPos()][character.getMapXPos()];
					entityBoard[character.getMapYPos()][character.getMapXPos()] = 0;
					character.setMapY(y);
				}
				newPos.x = x * 32;
				newPos.y = y * 32 - 32;
				return newPos;
			}
			else {
			}
			y--;
			if (y <= 1) {
				entityBoard[y][x] = entityBoard[character.getMapYPos()][character.getMapXPos()];
				entityBoard[character.getMapYPos()][character.getMapXPos()] = 0;
				character.setMapY(y);
			}
		}
		newPos.x = x * 32;
		newPos.y = y * 32 - 32;
		return newPos;
	case WayType::DOWN:
		while (y < 16) {
			if (gameBoard[y + 1][x] == 0 ||	gameBoard[y + 1][x] == 2 ||
				gameBoard[y + 1][x] == 4 ||	gameBoard[y + 1][x] == 5 ||
				gameBoard[y + 0][x] == 6 ||	gameBoard[y + 0][x] == 7 ||
				(entityBoard[y + 1][x] >= 2 && entityBoard[y + 1][x] <= 6))
			{
				if (x != character.getMapXPos() || y != character.getMapYPos()) {
					entityBoard[y][x] = entityBoard[character.getMapYPos()][character.getMapXPos()];
					entityBoard[character.getMapYPos()][character.getMapXPos()] = 0;
					character.setMapY(y);
				}
				newPos.x = x * 32;
				newPos.y = y * 32 - 32;
				return newPos;
			}
			else {
			}
			y++;
			if (y >= 16) {
				entityBoard[y][x] = entityBoard[character.getMapYPos()][character.getMapXPos()];
				entityBoard[character.getMapYPos()][character.getMapXPos()] = 0;
				character.setMapY(y);
			}
		}
		newPos.x = x * 32;
		newPos.y = y * 32 - 32;
		return newPos;
	default:
		return SDL_Rect();
	}
}

//Print a string of current boards DEBUG
void GameLogic::printBoards()
{
	printf("\n");
	for (int y = 0; y < BOARDHEIGHT; y++) {
		printf("[ ");
		for (int x = 0; x < BOARDWIDTH; x++) {
			printf(std::to_string(entityBoard[y][x]).c_str(), " ");
		}
		printf("]\n");
	}
}

GameLogic::~GameLogic()
{
	gameBoard.clear();
	entityBoard.clear();
	orgEntityBoard.clear();
}

//Back upp entity board, to reset board if player regrets or wants to try again
void GameLogic::setBackupEntityBoard()
{
	orgEntityBoard = entityBoard;
}
