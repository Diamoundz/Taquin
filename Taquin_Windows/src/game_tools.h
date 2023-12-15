#ifndef GAME_TOOLS_INCLUDED
#define GAME_TOOLS_INCLUDED


int GetRandomNumber(int minIncluded,int maxIncluded);
int Wait(int millisecconds);
int Debug(int code);
int GetConsoleInput();
int DelayedPrint(char * message, int letterIntervalMillisecconds);

int ** MakeBoard();
int GetEmptySpaceIndex(int ** board);
int ShuffleBoard(int ** board, int depth);
int ConsoleDisplayBoard(int ** board);
int ClearBoardMem(int ** board);

int SerializeBoardToSaves(int ** board);
int GenerateGames();
int GetBoardFromSaves(int ** board);
int ClearSaveFile();

int TryMakeMove(int ** board ,int dir);
bool MakeMove(int ** board, int move);
bool CheckIfWin(int ** board);


#endif
