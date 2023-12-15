#ifndef RENDERING_TOOLS_INCLUDED
#define RENDERING_TOOLS_INCLUDED

SDL_Window* MakeWindow(int width, int height);
SDL_Renderer* MakeRenderer(SDL_Window* wind);
int ClearScreen(SDL_Renderer* rend);
int DestroyWindow(SDL_Window * wind, SDL_Renderer * rend);

#endif
