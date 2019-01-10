#include "MainMenu.h"



MainMenu::MainMenu()
{
}

bool MainMenu::init(SDL_Renderer *renderer, Options options)
{
	//TODO: load a background image or leave it as black
	//TODO: Load a title, Image or written text?

	this->options = options;
	//TODO: Font for start game, Multiplayer, options and exit
	menues.push_back(Gametext("Singelplayer"));
	menues.push_back(Gametext("Multiplayer"));
	menues.push_back(Gametext("Options"));
	menues.push_back(Gametext("Quit"));

//	for (Gametext g: menues) 
	for(int i = 0; i < menues.size();i++){
		menues[i].init("fonts/LCD_Solid.ttf");
		menues[i].setRandTextColor();
		menues[i].setTextRect((i + 1) * 29, (i + 1) * 29,
			menues[i].getText().length() * 24, 27);
		menues[i].makeTexture(renderer);
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	return false;
}




bool MainMenu::isInitialized()
{
	return !menues.empty();
}

State MainMenu::logic()
{
	while (SDL_PollEvent(&e) != 0) {
		int mouseX, mouseY;
		switch (e.type)
		{
		case SDL_QUIT:
			return State::QUIT;
		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&mouseX, &mouseY);
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				if (mouseX >= menues[0].getPos()->x && mouseX <= (menues[0].getPos()->x + menues[0].getPos()->w) && mouseY >= menues[0].getPos()->y && mouseY <= (menues[0].getPos()->y + menues[0].getPos()->h))
				{
					return State::GAME;
				}
				else if (mouseX >= menues[1].getPos()->x && mouseX <= (menues[1].getPos()->x + menues[1].getPos()->w) && mouseY >= menues[1].getPos()->y && mouseY <= (menues[1].getPos()->y + menues[1].getPos()->h))
				{
					printf("Not implemented yet!\n");
					return State::MAIN;
					return State::MULTI;
				}
				else if (mouseX >= menues[2].getPos()->x && mouseX <= (menues[2].getPos()->x + menues[2].getPos()->w) && mouseY >= menues[2].getPos()->y && mouseY <= (menues[2].getPos()->y + menues[2].getPos()->h))
				{
					printf("Not implemented yet!\n");
					return State::MAIN;
					return State::OPTIONS;
				}
				else if (mouseX >= menues[3].getPos()->x && mouseX <= (menues[3].getPos()->x + menues[3].getPos()->w) && mouseY >= menues[3].getPos()->y && mouseY <= (menues[3].getPos()->y + menues[3].getPos()->h))
				{
					return State::QUIT;
				}
			}
			break;
		case SDL_KEYDOWN:
			if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				return State::QUIT;
			}
		}
	}
	return State::MAIN;
}

void MainMenu::draw(SDL_Renderer* renderer)
{
	for (Gametext g : menues) {
		SDL_RenderCopy(renderer, g.getTexture(), NULL, g.getPos());
	}
}

MainMenu::~MainMenu()
{
	for (Gametext t : menues) {
		t.~Gametext();
	}
	menues.clear();

}
