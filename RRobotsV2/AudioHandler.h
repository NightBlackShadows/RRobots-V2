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

class AudioHandler
{
public:
	AudioHandler();

	bool loadMusic();
	void playMusic();
	void pauseMusic();
	void changeVolume(int volume);

	~AudioHandler();
private:
	int EffectVolume;
	std::vector<Mix_Music *> songs;
};

