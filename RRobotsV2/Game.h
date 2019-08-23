#pragma once
#include "GameLogic.h"
#include "Board.h"
#include "Character.h"
#include "Marker.h"
#include "Options.h"
#include "WayType.h"
#include "State.h"
#include <vector>
class Game
{
public:
	Game();
	bool initGame(SDL_Renderer* renderer,Options options);
	bool isInitialized();
	State runGame();
    bool unload();
	void drawGame(SDL_Renderer* renderer);
	~Game();
private:
    int time;
    SDL_Rect scoreboard;
	SDL_Event e;
	SDL_Rect dest;
	void sortCharacters();
	std::vector<std::vector<int>> entBoard;
	std::vector<Character> characters;
	std::vector<Marker> markers;
	std::vector<Character> marked;
	GameLogic gl;
	Board board;
	Options options;
	int markedCharacter;
	bool running;
	WayType way;
};

