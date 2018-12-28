#pragma once

#include <vector>
#include <stdint.h>
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

class AudioHandler
{
public:
  AudioHandler();

  bool initMusic();
  bool loadMusic();
  void playMusic();
  void pauseMusic();
  void changeVolume(int volume);

  ~AudioHandler();
private:
  int EffectVolume, frequency, channels, chunksize;
  uint16_t format;
  bool loaded;
  std::vector<Mix_Music *> songs;
};

