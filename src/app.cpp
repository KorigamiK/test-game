#include "app.h"

int Application::setupSDL()
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

void Application::handleEvents()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_q:
                running = false;
                printf("Q was pressed");
                break;
            default: printf("%d", event.type); break;
            }

        case SDL_QUIT: running = false; break;
        case SDL_CONTROLLERDEVICEADDED: SDL_GameControllerOpen(event.cdevice.which); break;
        case SDL_CONTROLLERBUTTONDOWN:
            if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START)
                running = false;
            break;
        }
    }
}

int Application::initApplication()
{
    printf("Starting game\n");
    if (this->setupSDL() != 0)
        return 1;

    if (TTF_Init() == -1)
        return 5;

    return 0;
}