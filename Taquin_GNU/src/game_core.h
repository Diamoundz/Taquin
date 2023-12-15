#ifndef GAME_CORE_INCLUDED
#define GAME_CORE_INCLUDED

int RenderImage(SDL_Renderer * rend,char * imageName, SDL_Rect * rect);
int WriteText(SDL_Renderer * rend, char * text, SDL_Color color, TTF_Font * font,bool centered, SDL_Rect rect);
int DisplayBoard(int ** board, SDL_Renderer * rend, TTF_Font * font);

int GetEvents();
int Stop();
int Start();
int Update();
int Awake();
int StartNewGame();



#endif
