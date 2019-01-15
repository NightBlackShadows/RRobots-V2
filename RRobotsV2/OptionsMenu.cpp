#include "OptionsMenu.h"



OptionsMenu::OptionsMenu()
{
}


bool OptionsMenu::init(SDL_Renderer* renderer, Options* options, WindowHandler* windowHandler, AudioHandler* audioHandler, MusicHandler* musicHandler)
{
	//TODO: load a background image or leave it as black
	//TODO: Load a title, Image or written text?

	this->options = options;
	this->windowHandler = windowHandler;
	this->audioHandler = audioHandler;
	this->musicHandler = musicHandler;

	//TODO: Font for start game, Multiplayer, options and exit
	optionMenues.push_back(Gametext("Screenres"));
	optionMenues.push_back(Gametext("Fullscreen"));
	optionMenues.push_back(Gametext("Mute"));
	optionMenues.push_back(Gametext("Volume music"));
	optionMenues.push_back(Gametext("Volume sounds"));
	optionMenues.push_back(Gametext("Exit"));

	//	for (Gametext g: optionMenues) 
	for (unsigned int i = 0; i < optionMenues.size(); i++) {
		optionMenues[i].init("fonts/LCD_Solid.ttf",renderer);
		optionMenues[i].setRandTextColor();
		optionMenues[i].setTextRect( 29, (i + 1) * 29,
			optionMenues[i].getText().length() * 24, 27);
		optionMenues[i].makeTexture();
	}

	changeMenuesValues.push_back(Gametext(std::to_string(options->getWidth()) + "x" + std::to_string(options->getHeight())));
	changeMenuesValues.push_back(Gametext(options->getFullscreenString()));
	changeMenuesValues.push_back(Gametext(options->getMuteString()));
	changeMenuesValues.push_back(Gametext(std::to_string(options->getMusicVolume())));
	changeMenuesValues.push_back(Gametext(std::to_string(options->getSoundVolume())));

	//	for (Gametext g: optionMenues) 
	for (unsigned int i = 0; i < changeMenuesValues.size(); i++) {
		changeMenuesValues[i].init("fonts/LCD_Solid.ttf",renderer);
		changeMenuesValues[i].setRandTextColor();
		changeMenuesValues[i].setTextRect(400, (i + 1) * 29,
			changeMenuesValues[i].getText().length() * 24, 27);
		changeMenuesValues[i].makeTexture();
	}

	return true;
}

bool OptionsMenu::isInitialized()
{
	return !optionMenues.empty();
}

State OptionsMenu::logic()
{
	while (SDL_PollEvent(&e) != 0) {
		int mouseX, mouseY;
		switch (e.type)
		{
		case SDL_QUIT:
			return State::QUIT;
		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&mouseX, &mouseY);
			//Would be good to change the constant [number] to something like 
			//optionMenues.where("Volume") so that you dont need to change the number if
			//you add more options
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				//Screen res
				if (mouseX >=optionMenues[0].getPos()->x &&
					mouseX <= (optionMenues[0].getPos()->x +optionMenues[0].getPos()->w) &&
					mouseY >=optionMenues[0].getPos()->y &&
					mouseY <= (optionMenues[0].getPos()->y +optionMenues[0].getPos()->h))
				{
				}
				//Fullscreen
				else if ((mouseX >= optionMenues[1].getPos()->x &&
					mouseX <= (optionMenues[1].getPos()->x + optionMenues[1].getPos()->w) &&
					mouseY >= optionMenues[1].getPos()->y &&
					mouseY <= (optionMenues[1].getPos()->y + optionMenues[1].getPos()->h)) ||
					(mouseX >= changeMenuesValues[1].getPos()->x &&
					mouseX <= (changeMenuesValues[1].getPos()->x + changeMenuesValues[1].getPos()->w) &&
					mouseY >= changeMenuesValues[1].getPos()->y &&
					mouseY <= (changeMenuesValues[1].getPos()->y + changeMenuesValues[1].getPos()->h)))
				{
					windowHandler->switchFullscreen(!options->getFullscreen());
					changeMenuesValues[1].setNewText(options->getFullscreenString());
				}
				//Mute
				else if ((mouseX >= optionMenues[2].getPos()->x &&
					mouseX <= (optionMenues[2].getPos()->x + optionMenues[2].getPos()->w) &&
					mouseY >= optionMenues[2].getPos()->y &&
					mouseY <= (optionMenues[2].getPos()->y + optionMenues[2].getPos()->h)) ||
					(mouseX >= changeMenuesValues[2].getPos()->x &&
					mouseX <= (changeMenuesValues[2].getPos()->x + changeMenuesValues[2].getPos()->w) &&
					mouseY >= changeMenuesValues[2].getPos()->y &&
					mouseY <= (changeMenuesValues[2].getPos()->y + changeMenuesValues[2].getPos()->h)))
				{
					options->setMute(!options->getMute());
					if (options->getMute()) {
						audioHandler->changeVolume(0);
						musicHandler->changeVolume(0);
					}
					else {
						audioHandler->changeVolume(options->getSoundVolume());
						musicHandler->changeVolume(options->getMusicVolume());
					}
					changeMenuesValues[2].setNewText(options->getMuteString());
				}
				//Music Volume
				else if (mouseX >= optionMenues[3].getPos()->x && 
					mouseX <= (optionMenues[3].getPos()->x + optionMenues[3].getPos()->w) &&
					mouseY >= optionMenues[3].getPos()->y && 
					mouseY <= (optionMenues[3].getPos()->y + optionMenues[3].getPos()->h))
				{
				}
				//SoundsVolume
				else if (mouseX >= optionMenues[4].getPos()->x &&
					mouseX <= (optionMenues[4].getPos()->x + optionMenues[4].getPos()->w) &&
					mouseY >= optionMenues[4].getPos()->y &&
					mouseY <= (optionMenues[4].getPos()->y + optionMenues[4].getPos()->h))
				{
				}
				//Exit
				else if (mouseX >= optionMenues[5].getPos()->x &&
					mouseX <= (optionMenues[5].getPos()->x + optionMenues[5].getPos()->w) &&
					mouseY >= optionMenues[5].getPos()->y &&
					mouseY <= (optionMenues[5].getPos()->y + optionMenues[5].getPos()->h))
				{
					return State::MAIN;
				}
			}
			
			break;
		case SDL_KEYDOWN:
			if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				return State::MAIN;
			}
		}
	}
	return State::OPTIONS;
}

void OptionsMenu::draw(SDL_Renderer* renderer)
{
	for (Gametext g : optionMenues) {
		SDL_RenderCopy(renderer, g.getTexture(), NULL, g.getPos());
	}
	for (Gametext g : changeMenuesValues) {
		SDL_RenderCopy(renderer, g.getTexture(), NULL, g.getPos());
	}
}

OptionsMenu::~OptionsMenu()
{

	for (Gametext t : optionMenues) {
		t.~Gametext();
	}
	optionMenues.clear();
	for (Gametext t : changeMenuesValues) {
		t.~Gametext();
	}
	changeMenuesValues.clear();
}
