#include "default_includes.h"
#include "rendering_tools.h"
#include "game_tools.h"
#include "game_core.h"

#define WIDTH 1600
#define HEIGHT 900

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

#define BOARD_SIZE 4

#define FPS 60

//define booleans as global variables for ease of manipulation
bool running = true, isPlayingConsoleVersion = false;

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
    return -1;
}

int Stop(){
    DestroyWindow(wind,rend);
    return 0;
}


int Start(){

    board = MakeBoard(BOARD_SIZE);
    ConsoleDisplayBoard(board,BOARD_SIZE);

    return 0;
}

int Update(){
    // Get events and input and refresh the screen

    int inputDirection = -1;
    if(!isPlayingConsoleVersion){
        inputDirection = GetEvents();
        ClearScreen(rend);
    }
    else{
        inputDirection = GetConsoleInput();
    }
    if(inputDirection!=-1){
        TryMakeMove(inputDirection);
    }

    return 0;
}

int TryMakeMove(int dir){
    ConsoleDisplayBoard(board,BOARD_SIZE);
}

int Awake(bool isConsoleVersion){

    isPlayingConsoleVersion = isConsoleVersion;

    srand(time(NULL));

    if(!isPlayingConsoleVersion){
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
        if(!isPlayingConsoleVersion){
            /* Draw to window and loop with delay*/
            SDL_RenderPresent(rend);
            SDL_Delay(1000/FPS);
        }
    }

    Stop();
}
