#pragma once
#include <SDL_image.h>
#include <vector>
#include "ColorType.h"
#include "Character.h"
#include "Marker.h"
#include "Board.h"
#include "Options.h"

class GameLogic
{
public:
	GameLogic();
	void randomizeCharacterPos(std::vector<Character>* characters);
	void randomizeMarker(std::vector<Marker>* markers);
	ColorType getCurrentMarker();
	void setGameBoard(std::vector<std::vector<int>> gameBoard);
	void setEntityBoard(std::vector<std::vector<int>> entityBoard);
	bool moveCharacter(Character character,WayType way);
	~GameLogic();

private:
	bool detectCollision(SDL_Rect character, SDL_Rect marker, WayType way);
	std::vector<std::vector<int>> gameBoard;
	std::vector<std::vector<int>> entityBoard;
	ColorType currentMarker;
	Options options;
};

