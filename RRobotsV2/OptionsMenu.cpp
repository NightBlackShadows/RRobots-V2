#include "OptionsMenu.h"



OptionsMenu::OptionsMenu(Options* options)
{
	this->options = options;
}


bool OptionsMenu::init(SDL_Renderer* renderer)
{
	//TODO: load a background image or leave it as black
	//TODO: Load a title, Image or written text?

	this->options = options;
	//TODO: Font for start game, Multiplayer, options and exit
	menues.push_back(Gametext("Screenres"));
	menues.push_back(Gametext("Fullscreen"));
	menues.push_back(Gametext("Volume music"));
	menues.push_back(Gametext("Volume sounds"));

	//	for (Gametext g: menues) 
	for (int i = 0; i < menues.size(); i++) {
		menues[i].init("fonts/LCD_Solid.ttf");
		menues[i].setRandTextColor();
		menues[i].setTextRect((i + 1) * 29, (i + 1) * 29,
			menues[i].getText().length() * 24, 27);
		menues[i].makeTexture(renderer);
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	return true;
}

bool OptionsMenu::isInitialized()
{
	return false;
}

State OptionsMenu::logic()
{
	return State();
}

void OptionsMenu::draw(SDL_Renderer* renderer)
{
}

OptionsMenu::~OptionsMenu()
{
}
