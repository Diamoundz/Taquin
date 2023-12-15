#include "definitions.h"
#include "rendering_tools.h"


SDL_Window* MakeWindow(int width, int height){
    /* Create a window */
    SDL_Window* wind = SDL_CreateWindow("Taquin",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        width, height, 0);
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

int RenderImage(SDL_Renderer * rend,char * imageName, SDL_Rect * rect){
    if(strlen(imageName)<=1){
        return 0;
    }
    char * pathName = malloc(sizeof(char)*(strlen(imageName)+strlen(SOURCE_PATH)+1));
    pathName[0] = '\0';

    strcat(pathName,SOURCE_PATH);
    strcat(pathName,imageName);

    SDL_Surface * image = IMG_Load(pathName);

    if(image == NULL){
        printf("Error : Failed to load image with path name %s - %s\n",pathName,SDL_GetError());
    }

    SDL_Texture * texture = SDL_CreateTextureFromSurface(rend,image);
    SDL_FreeSurface(image);
    SDL_RenderCopy(rend, texture, NULL, rect);
    SDL_DestroyTexture(texture);
    free(pathName);
    return 0;
}

int get_text_and_rect(SDL_Renderer* renderer, int x, int y, char* text,
    TTF_Font* font, SDL_Texture** texture, SDL_Rect* rect) {
    int text_width;
    int text_height;
    SDL_Surface* surface;
    SDL_Color textColor = { 255, 255, 255, 0 };

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
    return 0;
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

