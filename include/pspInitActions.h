#pragma once

#ifdef IS_PSP
#include <pspdebug.h>
#include <pspkernel.h>

void setup_exit_callback();
#endif

// SDL_RenderCopy(renderer, title, NULL, &titleRect);
// SDL_RenderPresent(renderer);
// SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
// SDL_RenderClear(renderer);
