#include "definitions.h"
#include "game_tools.h"

// Function to print debug information with a code
int Debug(int code) {
    printf("== Debug code: %d ==\n", code);
    return 0;
}

// Function to create a new game board
int **MakeBoard() {
    int **board = malloc(sizeof(int *) * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++) {
        int *row = malloc(sizeof(int) * BOARD_SIZE);
        for (int j = 0; j < BOARD_SIZE; j++) {
            row[j] = i * BOARD_SIZE + j + 1;
        }
        board[i] = row;
    }
    board[BOARD_SIZE - 1][BOARD_SIZE - 1] = 0;
    return board;
}

// Function to free memory allocated for the game board
int ClearBoardMem(int **board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        free(board[i]);
    }
    free(board);
    return 0;
}

// Function to generate a random number within a given range
int GetRandomNumber(int minIncluded, int maxIncluded) {
    return rand() % ((maxIncluded + 1) - (minIncluded)) + minIncluded;
}

// Function to display the game board in the console
int ConsoleDisplayBoard(int **board) {
    fflush(stdout);
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != 0) {
                printf("%2d%s", board[i][j], (j < BOARD_SIZE - 1) ? " | " : "");
            } else {
                printf("  %s", (j < BOARD_SIZE - 1) ? " | " : "");
            }
        }
        printf("\n");
        for (int j = 0; j < BOARD_SIZE * 4 + 2; j++) {
            printf("=");
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

// Function to clear the save file
int ClearSaveFile() {
    FILE *f = fopen(SAVE_FILE, "w+");
    if (f == NULL) {
        printf("Error: The specified file does not exist - %s.\n", SAVE_FILE);
        return -1;
    }
    fclose(f);
    return 0;
}

// Function to serialize the current board state and save to the file
int SerializeBoardToSaves(int **board) {
    FILE *f = fopen(SAVE_FILE, "a+");
    if (f == NULL) {
        printf("Error: The specified file does not exist - %s.\n", SAVE_FILE);
        return -1;
    }
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        fprintf(f, "%d ", board[(int)(i / BOARD_SIZE)][i % BOARD_SIZE]);
    }
    fputc('\n', f);

    fclose(f);
    return 0;
}

// Function to generate multiple games and save their initial states
int GenerateGames() {
    ClearSaveFile();
    for (int i = 0; i < SAVED_BOARD_COUNT; i++) {
        int **board = MakeBoard();
        ShuffleBoard(board, GetRandomNumber(MIN_BOARD_SHUFFLE, MAX_BOARD_SHUFFLE));
        if (CheckIfWin(board)) {
            ClearBoardMem(board);
            i--;
            break;
        }
        SerializeBoardToSaves(board);
        ClearBoardMem(board);
    }
    return 0;
}

// Function to read a board state from the saved file
int GetBoardFromSaves(int **board) {
    FILE *f = fopen(SAVE_FILE, "r");
    if (f == NULL) {
        printf("Error: The specified file does not exist - %s.\n", SAVE_FILE);
        return -1;
    }
    fseek(f, 0, SEEK_END);
    int charCount = ftell(f);
    fseek(f, 0, SEEK_SET);

    int lineLength = (charCount - 1) / (SAVED_BOARD_COUNT) + 1;
    int randomBoardIndex = GetRandomNumber(0, SAVED_BOARD_COUNT - 1);
    fseek(f, randomBoardIndex * lineLength, SEEK_SET);
    char c;
    int curDigitLen = 0;
    int boardIndex = 0;

    for (int i = 0; i < lineLength; i++) {
        c = fgetc(f);
        if (c == ' ' && curDigitLen > 0) {
            if (boardIndex >= BOARD_SIZE * BOARD_SIZE) {
                GenerateGames();
                GetBoardFromSaves(board);
            } else {
                char *numberString = malloc(sizeof(char) * (curDigitLen + 1));
                fseek(f, -curDigitLen - 1, SEEK_CUR);
                for (int j = 0; j < curDigitLen; j++) {
                    c = fgetc(f);
                    numberString[j] = c;
                }
                numberString[curDigitLen] = '\0';
                board[(int)(boardIndex / BOARD_SIZE)][boardIndex % BOARD_SIZE] = atoi(numberString);
                fseek(f, 1, SEEK_CUR);

                boardIndex++;
                curDigitLen = 0;
                free(numberString);
            }
        } else {
            curDigitLen++;
        }
    }
    if (boardIndex != BOARD_SIZE * BOARD_SIZE) {
        GenerateGames();
        GetBoardFromSaves(board);
    }
    fclose(f);
    return 0;
}

// Function to pause execution for a specified duration
int Wait(int milliseconds) {
    fflush(stdout);
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
    return 0;
}

// Function to shuffle the game board by making random moves
int ShuffleBoard(int **board, int depth) {
    int moves[4] = {LEFT, RIGHT, UP, DOWN};
    for (int i = 0; i < depth; i++) {
        int moveId = GetRandomNumber(0, 3);
        if (!MakeMove(board, moves[moveId])) {
            i--;
        }
    }
    return 0;
}

// Function to print a message with a delay between letters
int DelayedPrint(char *message, int letterIntervalMilliseconds) {
    int len = strlen(message);
    for (int i = 0; i < len; i++) {
        Wait(letterIntervalMilliseconds);
        printf("%c", message[i]);
    }
    printf("\n");
    return 0;
}

// Function to check if the current board state is a winning state
bool CheckIfWin(int **board) {
    bool isWin = true;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; (j < BOARD_SIZE) && ((i * BOARD_SIZE + j + 1) < BOARD_SIZE * BOARD_SIZE); j++) {
            if (board[i][j] != (i * BOARD_SIZE + j + 1)) {
                isWin = false;
            }
        }
    }
    return isWin;
}

// Function to get the index of the empty space on the board
int GetEmptySpaceIndex(int **board) {
    int index = -1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                index = i * BOARD_SIZE + j;
            }
        }
    }
    return index;
}

// Function to make a move on the board
bool MakeMove(int **board, int move) {
    int direction = move;
    int index = GetEmptySpaceIndex(board);
    int row = (int)(index / BOARD_SIZE);
    int col = index % BOARD_SIZE;
    if (direction < 2) {
        // Move left or right
        if (col + direction <= BOARD_SIZE - 1 && col + direction >= 0) {
            board[row][col] = board[row][col + direction];
            board[row][col + direction] = 0;
            return true;
        }
    } else {
        // Move up or down
        direction -= 3;
        if (row + direction <= BOARD_SIZE - 1 && row + direction >= 0) {
            board[row][col] = board[row + direction][col];
            board[row + direction][col] = 0;
            return true;
        }
    }
    return false;
}

// Function to attempt making a move and display the updated board
int TryMakeMove(int **board, int dir) {
    if (MakeMove(board, dir)) {
        ConsoleDisplayBoard(board);
    } else {
        printf("This move is illegal. Please try again.\n");
    }
    return 0;
}

// Function to get user input for console version
int GetConsoleInput() {
    char c;
    printf("Please enter your move === g(left), d(right), h(up), b(down) === : ");
    scanf("\n%c", &c);
    int choice = NO_DIR;
    switch (c) {
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
            printf("Error: Please enter one of the following - g(left), d(right), h(up), b(down)\n");
            break;
    }
    return choice;
}

