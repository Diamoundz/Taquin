#include "default_includes.h"
#include "game_tools.h"

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3


int Debug(int code){
    printf("== Debug code : %d ==\n",code);
    return 0;
}

int ** MakeBoard(int boardSize){
    int ** board = malloc(sizeof(int*)*boardSize);
    for(int i =0; i <boardSize;i++){
        int * row = malloc(sizeof(int)*boardSize);
        for(int j = 0; j<boardSize; j++){
            row[j]= i * boardSize + j + 1;
        }
        board[i]=row;
    }
    board[boardSize-1][boardSize-1] = -1;
    return board;
}

int GetRandomNumber(int minIncluded,int maxIncluded){
    return rand()%((maxIncluded+1)-(minIncluded))+minIncluded;
}

int ConsoleDisplayBoard(int ** board, size_t boardSize){
    //check if board is empty
    if(boardSize == 0){
        printf("Error : board is empty\n");
        return -1;
    }
    for(int i = 0; i<boardSize; i++){
        for(int j = 0; j<boardSize; j++){
            if(board[i][j] != -1){
                printf("%2d%s",board[i][j],(j<boardSize-1)?" | ":"");
            }
            else{
                printf(" %s",(j<boardSize-1)?" | ":"");
            }
        }
        printf("\n");
        for(int j = 0; j<boardSize*4 +2; j++){
            printf("=");
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

int GetConsoleInput(){
    char c;
    printf("Please enter your move === g(left),d(right),h(up),b(down) === : ");
    scanf("\n%c",&c);
    int choice = -1;
    switch (c){
        case 'g':
            choice = LEFT;
            break;
        case 'd':
            choice = RIGHT;
            break;
        case 'h':
            choice = UP;
            break;
        case 'b':
            choice = DOWN;
            break;
        default:
            printf("Error: Please enter one of the following - g(left),d(right),h(up),b(down)\n");
            break;
    }
    return choice;
}
