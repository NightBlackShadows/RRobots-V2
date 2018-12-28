#pragma once

#include <vector>
#ifdef _WIN32
#include <SDL.h>
#include <SDL_mixer.h>
#endif
#ifdef __APPLE__ 
#endif
#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
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

