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

	SDL_GetWindowDisplayMode(windowHandler->getWindow(), &current);
	//	for (Gametext g: optionMenues)
	for (unsigned int i = 0; i < optionMenues.size(); i++) {
		optionMenues[i].init("fonts/LCD_Solid.ttf",renderer);
		optionMenues[i].setTextColor();
		optionMenues[i].setTextRect( current.w *0.04, (i + 1) * 29,
		optionMenues[i].getText().length() * 24, 27);
		optionMenues[i].makeTexture();
	}

	optionMenues[optionMenues.size()-1].setTextRect(
		(current.w *0.04),
		(current.h - (current.h * 0.04) - 27),
		optionMenues[optionMenues.size()-1].getText().length() * 24, 27);

		changeMenuesValues.push_back(Gametext(std::to_string(current.w) + "x" + std::to_string(current.h)));
		changeMenuesValues.push_back(Gametext(options->getFullscreenString()));
		changeMenuesValues.push_back(Gametext(options->getMuteString()));
		changeMenuesValues.push_back(Gametext(std::to_string(options->getMusicVolume())));
		changeMenuesValues.push_back(Gametext(std::to_string(options->getSoundVolume())));

		//	for (Gametext g: optionMenues)
		for (unsigned int i = 0; i < changeMenuesValues.size(); i++) {
			int textLenthDiv2 = (changeMenuesValues[i].getText().length() * 24)/2;
			changeMenuesValues[i].init("fonts/LCD_Solid.ttf",renderer);
			changeMenuesValues[i].setTextColor();
			changeMenuesValues[i].setTextRect(568-textLenthDiv2, (i + 1) * 29,
			changeMenuesValues[i].getText().length() * 24, 27);
			changeMenuesValues[i].makeTexture();
		}

		for(int i = 0; i < changeMenuesValues.size(); i++){
			arrowMenues.push_back(Gametext("<"));
			arrowMenues.push_back(Gametext(">"));
		}
		for(int i = 0; i < arrowMenues.size(); i++){
			arrowMenues[i].init("fonts/LCD_Solid.ttf",renderer);
			arrowMenues[i].setTextColor();
			if(i%2 == 0)
			arrowMenues[i].setTextRect(376, (i/2 + 1)* 29, 24, 27);
			else
			arrowMenues[i].setTextRect(736, (i/2 + 1)* 29, 24, 27);
			arrowMenues[i].makeTexture();
		}

		fillDisplayModes();

		return true;
	}

	void OptionsMenu::fillDisplayModes(){
		static int display_in_use = 0; /* Only using first display */

		int i, display_mode_count;
		SDL_DisplayMode mode;
		Uint32 f;

		display_mode_count = SDL_GetNumDisplayModes(display_in_use);
		if (display_mode_count < 1) {
			SDL_Log("SDL_GetNumDisplayModes failed: %s", SDL_GetError());
			//return 1;
		}

		for (i = 0; i < display_mode_count; ++i) {
			if (SDL_GetDisplayMode(display_in_use, i, &mode) != 0) {
				SDL_Log("SDL_GetDisplayMode failed: %s", SDL_GetError());
				//return 1;
			}
			// TODO fixa olika för olika refresh rates
			if(mode.w >= 800 && mode.refresh_rate == 60){
				displayModes.push_back(mode);
			}
		}
		for(int i = 0; i < displayModes.size(); i++){
			if(current.w == displayModes[i].w && current.h == displayModes[i].h)
			currentModePlace = i;
		}
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
				//Screen res down
				if (mouseX >= arrowMenues[0].getPos()->x &&
				mouseX <= (arrowMenues[0].getPos()->x + arrowMenues[0].getPos()->w) &&
				mouseY >= arrowMenues[0].getPos()->y &&
				mouseY <= (arrowMenues[0].getPos()->y + arrowMenues[0].getPos()->h))
				{
					if(currentModePlace == displayModes.size()-1)
						currentModePlace = 0;
					else
						currentModePlace++;
					current = displayModes[currentModePlace];
					options->setResolution(current.w,current.h);
					windowHandler->setResolution(current.w,current.h);
					changeMenuesValues[0].setNewText(std::to_string(current.w) + "x" + std::to_string(current.h));
					adjustExit();
					adjustText(0);
				}
				//Screen res up
				else if (mouseX >= arrowMenues[1].getPos()->x &&
				mouseX <= (arrowMenues[1].getPos()->x + arrowMenues[1].getPos()->w) &&
				mouseY >= arrowMenues[1].getPos()->y &&
				mouseY <= (arrowMenues[1].getPos()->y + arrowMenues[1].getPos()->h))
				{
					if(currentModePlace == 0)
						currentModePlace = displayModes.size()-1;
					else
						currentModePlace--;
					current = displayModes[currentModePlace];
					options->setResolution(current.w,current.h);
					windowHandler->setResolution(current.w,current.h);
					changeMenuesValues[0].setNewText(std::to_string(current.w) + "x" + std::to_string(current.h));
					adjustExit();
					adjustText(0);
				}
				//Fullscreen
				else if ((mouseX >= arrowMenues[2].getPos()->x &&
				mouseX <= (arrowMenues[2].getPos()->x + arrowMenues[2].getPos()->w) &&
				mouseY >= arrowMenues[2].getPos()->y &&
				mouseY <= (arrowMenues[2].getPos()->y + arrowMenues[2].getPos()->h)) ||
				(mouseX >= arrowMenues[3].getPos()->x &&
				mouseX <= (arrowMenues[3].getPos()->x + arrowMenues[3].getPos()->w) &&
				mouseY >= arrowMenues[3].getPos()->y &&
				mouseY <= (arrowMenues[3].getPos()->y + arrowMenues[3].getPos()->h)))
				{
					windowHandler->switchFullscreen(!options->getFullscreen());
					changeMenuesValues[1].setNewText(options->getFullscreenString());
					adjustText(1);
				}
				//Mute
				else if ((mouseX >= arrowMenues[4].getPos()->x &&
				mouseX <= (arrowMenues[4].getPos()->x + arrowMenues[4].getPos()->w) &&
				mouseY >= arrowMenues[4].getPos()->y &&
				mouseY <= (arrowMenues[4].getPos()->y + arrowMenues[4].getPos()->h)) ||
				(mouseX >= arrowMenues[5].getPos()->x &&
				mouseX <= (arrowMenues[5].getPos()->x + arrowMenues[5].getPos()->w) &&
				mouseY >= arrowMenues[5].getPos()->y &&
				mouseY <= (arrowMenues[5].getPos()->y + arrowMenues[5].getPos()->h)))
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
					adjustText(2);
				}
				//Music Volume down
				else if (mouseX >= arrowMenues[6].getPos()->x &&
				mouseX <= (arrowMenues[6].getPos()->x + arrowMenues[6].getPos()->w) &&
				mouseY >= arrowMenues[6].getPos()->y &&
				mouseY <= (arrowMenues[6].getPos()->y + arrowMenues[6].getPos()->h))
				{
					if(options->getMusicVolume() >= 10){
						options->setMusicVolume(options->getMusicVolume()-10);
						if(!options->getMute()){
							musicHandler->changeVolume(options->getMusicVolume());
						}
					}else{
						options->setMusicVolume(0);
						musicHandler->changeVolume(0);
					}
					changeMenuesValues[3].setNewText(std::to_string(options->getMusicVolume()));
					adjustText(3);
				}
				//Music Volume up
				else if (mouseX >= arrowMenues[7].getPos()->x &&
				mouseX <= (arrowMenues[7].getPos()->x + arrowMenues[7].getPos()->w) &&
				mouseY >= arrowMenues[7].getPos()->y &&
				mouseY <= (arrowMenues[7].getPos()->y + arrowMenues[7].getPos()->h))
				{
					if(options->getMusicVolume() <= 90){
						options->setMusicVolume(options->getMusicVolume()+10);
						if(!options->getMute()){
							musicHandler->changeVolume(options->getMusicVolume());
						}
					}else{
						options->setMusicVolume(100);
						if(!options->getMute()){
							musicHandler->changeVolume(100);
						}
					}
					changeMenuesValues[3].setNewText(std::to_string(options->getMusicVolume()));
					adjustText(3);
				}
				//Sound Volume down
				else if (mouseX >= arrowMenues[8].getPos()->x &&
				mouseX <= (arrowMenues[8].getPos()->x + arrowMenues[8].getPos()->w) &&
				mouseY >= arrowMenues[8].getPos()->y &&
				mouseY <= (arrowMenues[8].getPos()->y + arrowMenues[8].getPos()->h))
				{
					if(options->getSoundVolume() >= 10){
						options->setSoundVolume(options->getSoundVolume()-10);
						if(!options->getMute()){
							audioHandler->changeVolume(options->getSoundVolume());
						}
					}else{
						options->setSoundVolume(0);
						audioHandler->changeVolume(0);
					}
					changeMenuesValues[4].setNewText(std::to_string(options->getSoundVolume()));
					adjustText(4);
				}
				//Sound Volume up
				else if (mouseX >= arrowMenues[9].getPos()->x &&
				mouseX <= (arrowMenues[9].getPos()->x + arrowMenues[9].getPos()->w) &&
				mouseY >= arrowMenues[9].getPos()->y &&
				mouseY <= (arrowMenues[9].getPos()->y + arrowMenues[9].getPos()->h))
				{
					if(options->getSoundVolume() <= 90){
						options->setSoundVolume(options->getSoundVolume()+10);
						if(!options->getMute()){
							audioHandler->changeVolume(options->getSoundVolume());
						}
					}else{
						options->setSoundVolume(100);
						if(!options->getMute()){
							audioHandler->changeVolume(100);
						}
					}
					changeMenuesValues[4].setNewText(std::to_string(options->getSoundVolume()));
					adjustText(4);
				}
				//Exit
				else if (mouseX >= optionMenues[optionMenues.size()-1].getPos()->x &&
				mouseX <= (optionMenues[optionMenues.size()-1].getPos()->x + optionMenues[optionMenues.size()-1].getPos()->w) &&
				mouseY >= optionMenues[optionMenues.size()-1].getPos()->y &&
				mouseY <= (optionMenues[optionMenues.size()-1].getPos()->y + optionMenues[optionMenues.size()-1].getPos()->h))
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
	for(Gametext g : arrowMenues){
		SDL_RenderCopy(renderer, g.getTexture(), NULL, g.getPos());
	}
}

void OptionsMenu::adjustText(int index){
	changeMenuesValues[index].setTextRect(568-(changeMenuesValues[index].getText().length()*24)/2, (index+1) * 29,
	changeMenuesValues[index].getText().length() * 24, 27);
}

void OptionsMenu::adjustExit(){

		optionMenues[optionMenues.size()-1].setTextRect(
			(current.w *0.04),
			(current.h - (current.h * 0.04) - 27),
			optionMenues[optionMenues.size()-1].getText().length() * 24, 27);
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
	displayModes.clear();
}
