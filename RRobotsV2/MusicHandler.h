#pragma once

#include <vector>
#ifdef _WIN32
#include <SDL.h>
#include <SDL_mixer.h>
#endif
#if defined __APPLE__ | defined __LINUX__
#include <SDL2/SDL2.h>
#include <SDL2_image/SDL_mixer.h>
#endif

class MusicHandler
{
public:
	MusicHandler();

	bool initMusic();
	bool loadMusic();
	int getNrOfLoadedSongs();
	int getVolume();
	void playMusic();
	void pauseMusic();
	void changeVolume(int volume);

	~MusicHandler();
private:
	bool loaded;
	int MusicVolume, numtimesopened, frequency, channels, chunksize;
	Uint16 format;
	std::vector<Mix_Music*> songs;


};

