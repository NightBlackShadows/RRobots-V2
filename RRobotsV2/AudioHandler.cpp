#include "AudioHandler.h"
#include <stdio.h>

//Constructor
AudioHandler::AudioHandler()
{
	this->loaded = false;
	this->frequency = 22050;
	this->channels = 2;
	this->chunksize = 4096;
	this->format = MIX_DEFAULT_FORMAT;
}



bool AudioHandler::initSounds()
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

// Load game sounds
bool AudioHandler::loadSounds()
{

	return false;
}

//Play a specifik sound
void AudioHandler::playSound()
{
}

//Pause a sound
void AudioHandler::pauseSound()
{
}

//Change volume for sounds
void AudioHandler::changeVolume(int volume)
{
	this->EffectVolume = volume;
}

AudioHandler::~AudioHandler()
{
}
