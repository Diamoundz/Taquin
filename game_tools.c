#include "default_includes.h"
#include "rendering_tools.h"

#define SIZE 20
#define WIDTH 1600
#define HEIGHT 900

#define FPS 60



int ** MakeBoard(int boardSize){
    int ** board = malloc(sizeof(int*)*boardSize);
    for(int i =0; i <boardSize;i++){
        int * row = malloc(sizeof(int)*boardSize);
        for(int j = 0; j<boardSize; j++){
            row[j]= i*boardSize + j;
        }
        board[i]=row;
    }
    board[boardSize-1][boardSize-1] = -1;
}



int GetRandomNumber(int minIncluded,int maxIncluded){
    return rand()%((maxIncluded+1)-(minIncluded))+minIncluded;
}

int InitGame(){

    srand(time(NULL));

    /* Initializes the timer, audio, video, joystick,
    haptic, gamecontroller and events subsystems */
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 0;
    }
}

int QuitGame(){

    return 0;
}

int GameLoop(){


    SDL_Window* wind= MakeWindow(WIDTH,HEIGHT);
    SDL_Renderer* rend = MakeRenderer(wind);



    SDL_Rect * rectList = malloc(sizeof(SDL_Rect)*10);

    for(int i=0; i< 10; i++){
        SDL_Rect rect = {(int) 0, 0, SIZE, SIZE};
        rectList[i] = rect;
    }

    SDL_Event event;

    bool running = true, up_pressed = false, down_pressed = false,
    left_pressed = false, right_pressed = false;

    while (running)
    {
        /* Process events */
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = false;
                    QuitGame();
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                        case SDL_SCANCODE_ESCAPE:
                            running = false;
                            QuitGame();
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            down_pressed = true;
                            break;
                        case SDL_SCANCODE_Q:
                        case SDL_SCANCODE_LEFT:
                            left_pressed = true;
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            right_pressed = true;
                            break;
                        case SDL_SCANCODE_Z:
                        case SDL_SCANCODE_UP:
                            up_pressed = true;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.scancode)
                    {
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            down_pressed = false;
                            break;
                        case SDL_SCANCODE_Q:
                        case SDL_SCANCODE_LEFT:
                            left_pressed = false;
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            right_pressed = false;
                            break;
                        case SDL_SCANCODE_Z:
                        case SDL_SCANCODE_UP:
                            up_pressed = false;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        ClearScreen(rend);






        /* Draw to window and loop with delay*/
        SDL_RenderPresent(rend);
        SDL_Delay(1000/FPS);
    }

    DestroyWindow(wind,rend);
    return 0;
}
