#include "definitions.h"
#include "game_tools.h"




int Debug(int code){
    printf("== Debug code : %d ==\n",code);
    return 0;
}

int ** MakeBoard(){
    int ** board = malloc(sizeof(int*)*BOARD_SIZE);
    for(int i =0; i <BOARD_SIZE;i++){
        int * row = malloc(sizeof(int)*BOARD_SIZE);
        for(int j = 0; j<BOARD_SIZE; j++){
            row[j]= i * BOARD_SIZE + j + 1;
        }
        board[i]=row;
    }
    board[BOARD_SIZE-1][BOARD_SIZE-1] = -1;
    return board;
}

int GetRandomNumber(int minIncluded,int maxIncluded){
    return rand()%((maxIncluded+1)-(minIncluded))+minIncluded;
}

int ConsoleDisplayBoard(int ** board){
    system("clear");
    for(int i = 0; i<BOARD_SIZE; i++){
        for(int j = 0; j<BOARD_SIZE; j++){
            if(board[i][j] != -1){
                printf("%2d%s",board[i][j],(j<BOARD_SIZE-1)?" | ":"");
            }
            else{
                printf("  %s",(j<BOARD_SIZE-1)?" | ":"");
            }
        }
        printf("\n");
        for(int j = 0; j<BOARD_SIZE*4 +2; j++){
            printf("=");
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

bool CheckIfWin(int ** board){
    bool isWin = true;
    for(int i =0; i <BOARD_SIZE;i++){
        for(int j = 0; (j<BOARD_SIZE) && ((i * BOARD_SIZE + j + 1) < BOARD_SIZE*BOARD_SIZE); j++){
            if(board[i][j] != (i * BOARD_SIZE + j + 1)){
                isWin = false;
            }
        }
    }
    return isWin;
}

int GetEmptySpaceIndex(int ** board){
    int index = -1;
    for(int i = 0; i<BOARD_SIZE; i++){
        for(int j = 0; j<BOARD_SIZE; j++){
            if(board[i][j] == -1){
                index = i*BOARD_SIZE+j;
            }
        }
    }
    return index;
}

bool MakeMove(int ** board, int move){
    int direction = move;
    int index = GetEmptySpaceIndex(board);
    int row = (int)(index/BOARD_SIZE);
    int col = index%BOARD_SIZE;
    if(direction<2){
        //move left or right
        if(col + direction <= BOARD_SIZE-1 &&  col + direction >= 0){
            board[row][col] = board[row][col + direction];
            board[row][col + direction] = -1;
            return true;
        }
    }
    else{
        //move up or down
        direction-= 3;
        if(row + direction <= BOARD_SIZE-1 &&  row + direction >= 0){
            board[row][col] = board[row + direction][col];
            board[row + direction][col] = -1;
            return true;
        }
    }
    return false;
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
