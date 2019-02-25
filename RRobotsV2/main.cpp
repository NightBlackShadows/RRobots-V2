#include <iostream>
#include <string>
#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#endif
#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#endif
#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif
#include "Game.h"
#include "Options.h"
#include "MusicHandler.h"
#include "WindowHandler.h"
#include "MainMenu.h"
#include "OptionsMenu.h"
#include "Timer.h"
#include "State.h"


//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

SDL_Renderer* renderer = NULL;

MainMenu mainMenu;
OptionsMenu optionsMenu;
Game game;
Options options;
WindowHandler wh;
MusicHandler mh;
AudioHandler ah;
SDL_DisplayMode *currentDisp;
bool init();
void draw();
void close();
State switchState();

State current;

int FPS_LOCK = 60;

int main(int argc, char* args[]) {
  //Start up SDL and create window

  bool running = true;
  //The frames per second timer
  Timer fpsTimer;

  //The frames per second cap timer
  Timer capTimer;



  if (!init())
    {
      printf("Failed to initialize!\n");
    }
  else
    {

      //Start counting frames per second
      int countedFrames = 0;
      int SCREEN_TICKS_PER_FRAME = 1000 / FPS_LOCK;
      fpsTimer.start();
      while (running) {

        capTimer.start();

        //Calculate and correct fps
        float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
        if (avgFPS > 2000000)
          {
            avgFPS = 0;
          }

        switch (current) {
        case State::MAIN:
          if (mainMenu.isInitialized()) {
            current = mainMenu.logic();
            mainMenu.draw(renderer);
            if (current != State::MAIN) {
              //mainMenu.~MainMenu();
              wh.clearScreen();
            }
          }
          else {
            mainMenu.init(renderer, &options);
          }
          break;
        case State::OPTIONS:
          if (optionsMenu.isInitialized()) {
            current = optionsMenu.logic();
            optionsMenu.draw(renderer);
            if (current != State::OPTIONS) {
              //optionsMenu.~OptionsMenu();
              wh.clearScreen();
            }
          }
          else {
            optionsMenu.init(renderer, &options, &wh, &ah, &mh);
          }
          break;
        case State::GAME:
          if (game.isInitialized()) {
            current = game.runGame();
            game.drawGame(renderer);
            if (current != State::GAME) {
              //game.~Game();
              wh.clearScreen();
            }
          }
          else {
            game.initGame(renderer, options);
          }
          break;
        case State::QUIT:
          running = false;
        default:
          break;
        }

        draw();
        ++countedFrames;
        //If frame finished early
        int frameTicks = capTimer.getTicks();
        if (frameTicks < SCREEN_TICKS_PER_FRAME)
          {
            //Wait remaining time
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
          }
      }
    }
	

  //Free resources and close SDL
  close();

  return 0;
}

void draw() {

  //Vill man testa att skriva ut något på bilden så gör det här!

  //SDL_RenderClear(renderer);
  //Update screen
  //game.drawGame(renderer);

  SDL_RenderPresent(renderer);
  wh.clearScreen();
}


bool init() {
  //Initialization flag
  bool success = true;

  options.loadOptions();
  FPS_LOCK = options.getFPSLock();
  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) == 0)

    {
      
      if (mh.initMusic()) {
        if (mh.loadMusic()) {
          if (!options.getMute()) {
            mh.changeVolume(options.getMusicVolume());
          }
          else {
            mh.changeVolume(0);
          }
          mh.playMusic();
        }
        else {
          printf("Some or all music could not be loaded\n");
        }
      }
      
      if (ah.initSounds()) {
        if (ah.loadSounds()) {
          //ah.changeVolume(options.getSoundVolume());
          //ah.playMusic();
        }
        else {
          printf("Some or all sounds could not be loaded\n");
        }
      }
      
      //Create window
      gWindow = SDL_CreateWindow("RRobot 2.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, options.getWidth(), options.getHeight(), SDL_WINDOW_SHOWN);
      if (gWindow != NULL)
        {
          //Create renderer for window
          renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
          if (renderer != NULL)
            {
              //Initialize renderer color
              SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
              wh.initWindowHandler(gWindow,&options,renderer);

              //Initialize PNG loading
              int imgFlags = IMG_INIT_PNG;
              if ((IMG_Init(imgFlags) & imgFlags))
                {
                  wh.switchFullscreen(options.getFullscreen());
                }
              else
                {
                  printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                  success = false;
                }
              
              if (TTF_Init())
                {
                  printf("SDL_ttf could not initialize! ttf error: %s\n", TTF_GetError());
                }
            }
          else
            {
              printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
              success = false;
            }
        }
      else
        {
          printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
          success = false;
        }
    }
  else
    {
      printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
      success = false;
    }
  
  current = State::MAIN;
  return success;
}

void close() {
  //Free loaded image
  //SDL_DestroyTexture(gTexture);
  //gTexture = NULL;
  if(options.getFullscreen() == true){
    SDL_SetWindowFullscreen(gWindow, false);
  }

  options.saveOptions();
  options.~Options();
  mh.~MusicHandler();
  ah.~AudioHandler();


  //Destroy window
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(gWindow);
  //gWindow = NULL;
  //renderer = NULL;

  //Quit SDL subsystems
  //IMG_Quit();
  SDL_Quit();
}
