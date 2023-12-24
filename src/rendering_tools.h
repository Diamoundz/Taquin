#ifndef RENDERING_TOOLS_INCLUDED
#define RENDERING_TOOLS_INCLUDED
    #if CONSOLE_VERSION == 0
        SDL_Window* MakeSDLWindow(int width, int height);
        SDL_Renderer* MakeRenderer(SDL_Window* wind);
        int ClearScreen(SDL_Renderer* rend);
        int DestroySDLWindow(SDL_Window * wind, SDL_Renderer * rend);
    #endif
#endif
