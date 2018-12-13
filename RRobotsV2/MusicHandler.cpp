#include "MusicHandler.h"
#include <stdio.h>

MusicHandler::MusicHandler()
{
	loaded = false;
	frequency = 22050;
	channels = 2;
	chunksize = 4096;
	format = MIX_DEFAULT_FORMAT;
}

/*
This can load WAVE, MOD, MIDI, OGG, MP3 and FLAC
*/

bool MusicHandler::loadMusic()
{
	int numFiles = 3;
	//get something to check the map "resources/Music" for all files in there and load them.

	for (int i = 0; i < numFiles; i++) {
		
	}

	songs.push_back(Mix_LoadMUS("resources/Music/bensound-happyrock.mp3"));
	songs.push_back(Mix_LoadMUS("resources/Music/bensound-jazzyfrenchy.mp3"));
	songs.push_back(Mix_LoadMUS("resources/Music/bensound-thelounge.mp3"));

	if (songs.size() == 0) {
		printf("Mix_LoadMUS(/resources/music/\"): %s\n", Mix_GetError());
		return false;
	}

	return true;
}

int MusicHandler::getNrOfLoadedSongs()
{
	return songs.size();
}

int MusicHandler::getVolume()
{
	return MusicVolume;
}

bool MusicHandler::initMusic()
{
	//Initialize the music
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not init audio! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	if (Mix_OpenAudio(frequency, format, channels, chunksize) == -1)
	{
		printf("Could not init sdl mixer.\n");
		return false;
	}
	return true;
}

void MusicHandler::playMusic()
{
	if (!loaded) {
		// the randomizer will change. just boring listening to the same song all the time
		if (Mix_PlayMusic(songs.at(rand()%3), 1) == -1) {
			printf("Mix_PlayMusic: %s\n", Mix_GetError());
			// well, there's no music, but most games don't break without music...
		}
		loaded = true;
	}

	// check the music pause status
	if (Mix_PausedMusic()) {
		// resume music
		Mix_ResumeMusic();
	}
}

void MusicHandler::pauseMusic()
{
	// pause music
	Mix_PauseMusic();
}

void MusicHandler::changeVolume(int volume)
{
	// set music volume to volume
	Mix_VolumeMusic(volume);
}


MusicHandler::~MusicHandler()
{
	// get and print the audio format in use

	numtimesopened = Mix_QuerySpec(&frequency, &format, &channels);
	while (numtimesopened > 0) {
		Mix_CloseAudio();
		numtimesopened--;
	}

	for (int i = songs.size(); i > 0; i--) {
		Mix_FreeMusic(songs.at(i-1));
	}


	songs.clear();
}
