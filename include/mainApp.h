#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Application
{
public:
    bool running = true;
    const char* NAME = "Hello Test, KorigamiK";
    int WIDTH = 480;
    int HEIGHT = 272;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    void handleEvents();
    int initApplication();

private:
    int setupSDL();
};