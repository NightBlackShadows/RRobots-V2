#pragma once
#ifdef _WIN32
#include <SDL_image.h>
#endif
#if defined __APPLE__ | defined __LINUX__
#include <SDL2_image/SDL_image.h>
#endif
#include <vector>
#include "ColorType.h"
#include "Character.h"
#include "Marker.h"
#include "Board.h"
#include "Options.h"
#include <SDL_image.h>

class GameLogic
{
public:
	GameLogic();
	void randomizeCharacterPos(std::vector<Character>* characters);
	void randomizeMarker(std::vector<Marker>* markers);
	int changeMarked(std::vector<Character> &characters);
	std::vector<std::vector<int>> getEntityBoard();
	ColorType getCurrentMarker();
	void setGameBoard(std::vector<std::vector<int>> gameBoard);
	void setEntityBoard(std::vector<std::vector<int>> entityBoard);
	bool moveCharacter(Character &character,SDL_Rect dest);
	SDL_Rect detectCollision(Character &character, SDL_Rect marker, WayType way);
	~GameLogic();

private:
	std::vector<std::vector<int>> gameBoard;
	std::vector<std::vector<int>> entityBoard;
	ColorType currentMarker;
	Options options;
};

