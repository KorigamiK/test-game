#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "app.h"
#include "utils.h"

// PSP toggle for IDE
#define IS_PSP = 1

#ifdef IS_PSP
#include "pspInitActions.h"
#endif

int main(int argc, char* argv[])
{
#ifdef IS_PSP

    setup_exit_callback();
    pspDebugScreenSetBackColor(0xFFFFFFFF);
    pspDebugScreenSetTextColor(0);
    pspDebugScreenInit();
    pspDebugScreenSetXY(10, 5);
    pspDebugScreenPrintf("%s", utils::get_working_path().c_str());
    while (1)
    {
    }

#endif

    Application app;

    int initCode = app.initApplication();

    if (initCode != 0)
        return initCode;

    SDL_Rect square = {216, 96, 34, 64};
    TTF_Font* font = TTF_OpenFont("./assets/funkyFont.ttf", 20);

    if (font == NULL)
    {
        printf("TTF_OpenFont font error: %s\n %s", TTF_GetError(), utils::get_working_path().c_str());
        return 2;
    }

    SDL_Color fontColor = {0, 0, 0};
    SDL_Surface* surface1 = TTF_RenderUTF8_Blended(font, app.NAME, fontColor);
    if (surface1 == NULL)
    {
        printf("TTF_OpenFont surface: %s\n", TTF_GetError());
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to load create title! SDL Error: %s\n", SDL_GetError());
        return 3;
    }
    SDL_Texture* title = SDL_CreateTextureFromSurface(app.renderer, surface1);
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
    titleRect.x = app.WIDTH / 2 - titleRect.w / 2;
    titleRect.y = app.HEIGHT / 2 - titleRect.h / 2;

    while (app.running)
    {
        app.handleEvents();

        SDL_RenderCopy(app.renderer, title, NULL, &titleRect);
        SDL_RenderPresent(app.renderer);
        SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
        SDL_RenderClear(app.renderer);
    }

    return 0;
}