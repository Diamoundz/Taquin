#include "definitions.h"
#include "rendering_tools.h"
#include "game_tools.h"
#include "game_core.h"

//define booleans as global variables for ease of manipulation
bool running = true;

//keep track of the board
int ** board = NULL;

//keep track of the window, the renderer and the event fetcher as global variables
SDL_Window* wind= NULL;
SDL_Renderer* rend = NULL;


int GetEvents(){
    SDL_Event event;
    /* Process events */
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_ESCAPE:
                        running = false;
                        break;
                    case SDL_SCANCODE_S:
                    case SDL_SCANCODE_DOWN:
                        return DOWN;
                    case SDL_SCANCODE_A:
                    case SDL_SCANCODE_LEFT:
                        return LEFT;
                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        return RIGHT;
                    case SDL_SCANCODE_W:
                    case SDL_SCANCODE_UP:
                        return UP;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
    return NO_DIR;
}

int Stop(){
    if(CONSOLE_VERSION == 0){
        DestroyWindow(wind,rend);
    }

    return 0;
}


int Start(){

    board = MakeBoard();
    ShuffleBoard(board,300);
    ConsoleDisplayBoard(board);

    return 0;
}

int Update(){
    // Get events and input and refresh the screen

    int inputDirection = NO_DIR;
    if(CONSOLE_VERSION == 0){
        inputDirection = GetEvents();
        ClearScreen(rend);
    }
    else{
        inputDirection = GetConsoleInput();
    }
    if(inputDirection!=NO_DIR){
        TryMakeMove(inputDirection);
    }

    return 0;
}

int TryMakeMove(int dir){
    if(MakeMove(board,dir)){
        ConsoleDisplayBoard(board);
        if(CheckIfWin(board)){
            system("clear");
            ConsoleDisplayBoard(board);
            DelayedPrint("========= You Won ! =========\n",20);
        }
    }
    else{
        printf("This move is illegal, please try again.\n");
    }
    return 0;
}

int Awake(){

    srand(time(NULL));

    if(CONSOLE_VERSION == 0){
        /* Initializes the timer, audio, video, joystick,
        haptic, gamecontroller and events subsystems */
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            printf("Error initializing SDL: %s\n", SDL_GetError());
            return 0;
        }

        wind= MakeWindow(WIDTH,HEIGHT);
        rend = MakeRenderer(wind);
    }


    Start();

    while (running)
    {
        Update();
        if(CONSOLE_VERSION == 0){
            /* Draw to window and loop with delay*/
            SDL_RenderPresent(rend);
            SDL_Delay(1000/FPS);
        }
    }

    Stop();
}
