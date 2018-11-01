#include "Game.h"
#include <algorithm>

Game::Game()
{
}

bool Game::initGame(SDL_Renderer* renderer)
{
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
	characters.push_back(Character("resources/Characters/blue.png"));
	characters.push_back(Character("resources/Characters/green.png"));
	characters.push_back(Character("resources/Characters/black.png"));
	characters.push_back(Character("resources/Characters/red.png"));
	characters.push_back(Character("resources/Characters/yellow.png"));
	markers.push_back(Marker("resources/Marker/marker.png"));

	for (int i = 0; i < characters.size(); i++) {
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

	for (int i = 0; i < markers.size(); i++) {
		markers.at(i).loadImage(renderer);
		markers.at(i).defineImage(6);
	}

	gl.randomizeCharacterPos(&characters);
	gl.randomizeMarker(&markers);

	return true;
}

void Game::runGame()
{
	//sortCharacters();
}


void Game::drawGame(SDL_Renderer* renderer)
{
	//Draws the map
	for (int y = 0; y < BOARDHEIGHT; y++) {
		for (int x = 0; x < BOARDWIDTH; x++) {
			SDL_RenderCopy(renderer, board.getImageFromMap(x, y), NULL, board.getRectangle(x, y));
		}
	}



	for (int i = 0; i < markers.size(); i++) {
		SDL_RenderCopyEx(renderer, markers.at(i).getTexture(), markers.at(i).getSpriteRect(gl.getCurrentMarker()), markers.at(i).getPositionRect(), 0, NULL, SDL_FLIP_NONE);
	}
//	SDL_RenderCopyEx(renderer, marker->getTexture(), marker->getSpriteRect(ColorType::RED), marker->getPositionRect(), 0, NULL, SDL_FLIP_NONE);
	for (int i = 0; i < characters.size(); i++) {
		SDL_RenderCopyEx(renderer, characters.at(i).getTexture(), characters.at(i).getSpriteRect(WayType::NONE), characters.at(i).getPositionRect(), 0, NULL, SDL_FLIP_NONE);
	}
}

Game::~Game()
{
	board.~Board();
	gl.~GameLogic();
	for (int i = 0; i < characters.size(); i++) {
		characters.at(i).~Character();
	}
	for (int i = 0; i < markers.size(); i++) {
		markers.at(i).~Marker();
	}
	
}

void Game::sortCharacters()
{	
	//Character temp("");
	for (int i = 0; i < characters.size()-1; i++)
	{
		//compare elemet to the next element, and swap if condition is true
		for (int j = 0; j < characters.size() - i - 1; j++)
		{
			if (characters[j].compare(characters[j + 1])) {
				std::swap(characters.at(j), characters.at(j+1));				
			}
		}
	}
}
