#ifndef GAME_TOOLS_INCLUDED
#define GAME_TOOLS_INCLUDED

#include <stdlib.h>

int GetRandomNumber(int maxIncluded){
    return (int)(rand()%(maxIncluded+1));
}

#endif
