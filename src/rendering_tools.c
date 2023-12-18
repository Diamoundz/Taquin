#include "definitions.h"
#include "rendering_tools.h"

#if CONSOLE_VERSION == 0

    SDL_Window* MakeWindow(int width, int height){
        /* Create a window */

        SDL_Window* wind = SDL_CreateWindow("Taquin",
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            width, height, SDL_WINDOW_BORDERLESS);

        if (!wind)
        {
            printf("Error creating window: %s\n", SDL_GetError());
            SDL_Quit();
            return 0;
        }
        return wind;
    }
    SDL_Renderer* MakeRenderer(SDL_Window* wind){
        /* Create a renderer */
        Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
        SDL_Renderer* rend = SDL_CreateRenderer(wind, -1, render_flags);

        if (!rend)
        {
            printf("Error creating renderer: %s\n", SDL_GetError());
            SDL_DestroyWindow(wind);
            SDL_Quit();
            return 0;
        }
        return rend;
    }



    int ClearScreen(SDL_Renderer* rend){
        /* Clear screen */
        SDL_RenderClear(rend);
        return 0;
    }

    int DestroyWindow(SDL_Window * wind, SDL_Renderer * rend){
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(wind);
        SDL_Quit();
        return 0;
    }
#endif
