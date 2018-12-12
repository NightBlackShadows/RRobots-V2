#include "AudioHandler.h"



AudioHandler::AudioHandler()
{
	loaded = false;
	frequency = 22050;
	channels = 2;
	chunksize = 4096;
	format = MIX_DEFAULT_FORMAT;
}



bool AudioHandler::initMusic()
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

bool AudioHandler::loadMusic()
{

	return false;
}

void AudioHandler::playMusic()
{
}

void AudioHandler::pauseMusic()
{
}

void AudioHandler::changeVolume(int volume)
{
	this->EffectVolume = volume;
}


AudioHandler::~AudioHandler()
{
}
