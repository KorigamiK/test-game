#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// PSP toggle for IDE
// #define IS_PSP = 1

#ifdef IS_PSP
#include "pspInitActions.h"
#endif

#define NAME "Hello Test, KorigamiK"
#define WIDTH 480
#define HEIGHT 272

bool running = true;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int setupSdl()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    window = SDL_CreateWindow(NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initiation window. Error %s", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initialize renderer. Error: %s", SDL_GetError());
        return 1;
    }

    return 0;
}

void handleEvents()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT: running = 0; break;
        case SDL_CONTROLLERDEVICEADDED: SDL_GameControllerOpen(event.cdevice.which); break;
        case SDL_CONTROLLERBUTTONDOWN:
            if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START)
                running = false;
            break;
        }
    }
}

int main(int argc, char* argv[])
{
#ifdef IS_PSP

    setup_exit_callback();

#endif

    printf("Starting game\n");
    if (setupSdl() != 0)
        return 1;

    if (TTF_Init() == -1)
        return 5;

    SDL_Rect square = {216, 96, 34, 64};
    TTF_Font* font = TTF_OpenFont("./assets/funkyFont.ttf", 20);

    if (font == NULL)
    {
        printf("TTF_OpenFont font error: %s\n", TTF_GetError());
        return 2;
    }

    SDL_Color fontColor = {0, 0, 0};
    SDL_Surface* surface1 = TTF_RenderUTF8_Blended(font, NAME, fontColor);
    if (surface1 == NULL)
    {
        printf("TTF_OpenFont surface: %s\n", TTF_GetError());
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to load create title! SDL Error: %s\n", SDL_GetError());
        return 3;
    }
    SDL_Texture* title = SDL_CreateTextureFromSurface(renderer, surface1);
    if (title == NULL)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to load texture for image block.bmp! SDL Error: %s\n",
                     SDL_GetError());
        return 4;
    }
    SDL_FreeSurface(surface1);
    SDL_Rect titleRect;
    SDL_QueryTexture(title, NULL, NULL, &titleRect.w, &titleRect.h);
    titleRect.x = WIDTH / 2 - titleRect.w / 2;
    titleRect.y = HEIGHT / 2 - titleRect.h / 2;

    while (running)
    {
        handleEvents();

        SDL_RenderCopy(renderer, title, NULL, &titleRect);
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
    }

    return 0;
}