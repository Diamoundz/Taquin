#ifndef GAME_CORE_INCLUDED
#define GAME_CORE_INCLUDED

    #if CONSOLE_VERSION == 0
        int RenderImage(SDL_Renderer * rend,char * imageName, SDL_Rect * rect);
        int WriteText(SDL_Renderer * rend, char * text, SDL_Color color, TTF_Font * font,bool centered, SDL_Rect rect);
        int DisplayBoard(int ** board, SDL_Renderer * rend, TTF_Font * font);
        int Update();
    #endif

    int GetEvents();
    int Stop();
    int Start();
    int UpdateConsole();
    int Awake();
    int StartNewGame();



#endif
