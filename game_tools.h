#ifndef GAME_TOOLS_INCLUDED
#define GAME_TOOLS_INCLUDED

int ** MakeBoard();
int GetRandomNumber(int minIncluded,int maxIncluded);
int ConsoleDisplayBoard(int ** board);
int Debug(int code);
int GetConsoleInput();
int GetEmptySpaceIndex(int ** board);
bool MakeMove(int ** board, int move);
bool CheckIfWin(int ** board);

#endif
