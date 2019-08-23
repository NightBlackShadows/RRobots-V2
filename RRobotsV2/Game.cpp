#include "Game.h"
#include <algorithm>
#include <stdio.h>

Game::Game()
{
}

//Initialize game
bool Game::initGame(SDL_Renderer* renderer, Options options)
{
	this->options = options;
	board.initBoard();
	time = 20;
	if (board.loadImages(renderer)) {
		gl.setEntityBoard(board.getEntityBoard());
		gl.setGameBoard(board.getGameBoard());
	}
	else {
		return false;
	}
	/*
	In future get the name of enum to the filename to load the picture of the character
	for (int i = (int)ColorType::BLACK; i < (int)ColorType::YELLOW; i++) {

	}*/
	characters.push_back(Character("resources/Characters/green.png"));
	characters.push_back(Character("resources/Characters/blue.png"));
	characters.push_back(Character("resources/Characters/black.png"));
	characters.push_back(Character("resources/Characters/red.png"));
	characters.push_back(Character("resources/Characters/yellow.png"));
	markers.push_back(Marker("resources/Marker/marker.png"));
	marked.push_back(Character("resources/marked.png"));

	for (int i = 0; i < (int)characters.size(); i++) {
		if (characters.at(i).loadImage(renderer)) {
			if (characters.at(i).defineImage(4, 4)) {
				characters.at(i).setColor(i);
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}

	for (int i = 0; i < (int)markers.size(); i++) {
		markers.at(i).loadImage(renderer);
		markers.at(i).defineImage(6);
	}


	marked[0].loadImage(renderer);
	marked[0].defineImage(1, 1);

	gl.randomizeCharacterPos(&characters);
	gl.randomizeMarker(&markers);
	running = false;
	way = WayType::NONE;

	return true;
}

bool Game::isInitialized()
{
	return !characters.empty();
}


//Run game instance
State Game::runGame()
{
	if (way == WayType::NONE) {

		while(SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				return State::MAIN;
			}
			if (e.key.type == SDL_KEYDOWN) {
				if (e.key.keysym.scancode == SDL_SCANCODE_LEFT || e.key.keysym.scancode == SDL_SCANCODE_A) {
					way = WayType::LEFT;
				}
				else if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT || e.key.keysym.scancode == SDL_SCANCODE_D) {
					way = WayType::RIGHT;
				}
				else if (e.key.keysym.scancode == SDL_SCANCODE_DOWN || e.key.keysym.scancode == SDL_SCANCODE_S) {
					way = WayType::DOWN;
				}
				else if (e.key.keysym.scancode == SDL_SCANCODE_UP || e.key.keysym.scancode == SDL_SCANCODE_W) {
					way = WayType::UP;
				}
				else if (e.key.keysym.scancode == SDL_SCANCODE_R) {
				    //entBoard =
				}
				else if (e.key.keysym.scancode == SDL_SCANCODE_TAB) {
					markedCharacter = gl.changeMarked(characters);
				}
				else if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					return State::MAIN;
				}
			}
		}
	}
	else {
		if (dest.x == 0) {
			dest = gl.detectCollision(characters[markedCharacter], *markers.at(0).getPositionRect(), way);
		}
		if (!gl.moveCharacter(characters[markedCharacter], dest)) {
			way = WayType::NONE;
			dest.x = 0;
		}
	}

	if (gl.markerCollision(characters.at(markedCharacter), markers.at(0))) {
		gl.randomizeMarker(&markers);
	}

	return State::GAME;
	//sortCharacters();
}

//Draw current game
void Game::drawGame(SDL_Renderer* renderer)
{



	//To draw behind the map place over
	//Draws the map
	for (int y = 0; y < BOARDHEIGHT; y++) {
		for (int x = 0; x < BOARDWIDTH; x++) {
			SDL_RenderCopy(renderer, board.getImageFromMap(x, y), NULL, board.getRectangle(x, y));
		}
	}

	for (int i = 0; i < (int)markers.size(); i++) {
		SDL_RenderCopyEx(renderer, markers.at(i).getTexture(), markers.at(i).getSpriteRect(gl.getCurrentMarker()), markers.at(i).getPositionRect(), 0, NULL, SDL_FLIP_NONE);
	}

	//Draw over the map and the marker here

	entBoard = gl.getEntityBoard();

	for (int y = 1; y < BOARDHEIGHT - 1; y++) {
		for (int x = 1; x < BOARDWIDTH - 1; x++) {
			if (entBoard[y][x] >= 2 && entBoard[y][x] < 7) {
				if (characters.at(entBoard[y][x] - 2).getMarked()) {
					SDL_RenderCopy(renderer, marked.at(0).getTexture(), marked.at(0).getSpriteRect(WayType::NONE), characters.at(entBoard[y][x] - 2).getPositionRect());
					SDL_RenderCopyEx(renderer, characters.at(entBoard[y][x] - 2).getTexture(), characters.at(entBoard[y][x] - 2).getSpriteRect(way), characters.at(entBoard[y][x] - 2).getPositionRect(), 0, NULL, SDL_FLIP_NONE);
				}
				else {
					SDL_RenderCopyEx(renderer, characters.at(entBoard[y][x] - 2).getTexture(), characters.at(entBoard[y][x] - 2).getSpriteRect(WayType::NONE), characters.at(entBoard[y][x] - 2).getPositionRect(), 0, NULL, SDL_FLIP_NONE);
				}
			}
		}
	}
    SDL_SetRenderDrawColor(renderer, 211,211,211,0);
    scoreboard.x = options.getWidth()*0.72;
	scoreboard.y = 0;
	scoreboard.w = options.getWidth()*0.28;
	scoreboard.h = options.getHeight()*0.5;
    SDL_RenderFillRect(renderer, &scoreboard);
    SDL_SetRenderDrawColor(renderer, 0,0,0,0);

    SDL_RenderCopyEx(renderer, characters.at(markedCharacter).getTexture(), characters.at(markedCharacter).getSpriteRect(way), characters.at(markedCharacter).getPositionRect(), 0, NULL, SDL_FLIP_NONE);
}

bool Game::unload() {
    characters.clear();

}

//Destructor, clean memory
Game::~Game()
{

}

//Sort character for drawing
//TODO: check if in use
void Game::sortCharacters()
{
	//Character temp("");
	for (int i = 0; i < (int)characters.size()-1; i++)
	{
		//compare elemet to the next element, and swap if condition is true
		for (int j = 0; j < (int)characters.size() - i - 1; j++)
		{
			if (characters[j].compare(characters[j + 1])) {
				std::swap(characters.at(j), characters.at(j+1));
			}
		}
	}
}
