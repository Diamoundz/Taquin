#ifndef GAME_TOOLS_INCLUDED
#define GAME_TOOLS_INCLUDED

int ** MakeBoard(int boardSize);
int GetRandomNumber(int minIncluded,int maxIncluded);
int ConsoleDisplayBoard(int ** board, size_t boardSize);
int Debug(int code);
int GetConsoleInput();

#endif
