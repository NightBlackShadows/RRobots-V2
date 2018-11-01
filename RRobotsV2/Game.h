#pragma once
#include "GameLogic.h"
#include "Board.h"
#include "Character.h"
#include "Marker.h"
#include <vector>
class Game
{
public:
	Game();
	bool initGame(SDL_Renderer* renderer);

	void runGame();

	void drawGame(SDL_Renderer* renderer);
	~Game();
private:
	void sortCharacters();
	std::vector<Character> characters;
	std::vector<Marker> markers;
	GameLogic gl;
	Board board;

};

