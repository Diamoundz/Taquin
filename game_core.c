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
TTF_Font* font = NULL;
TTF_Font* titleFont = NULL;


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
    ClearBoardMem(board);
    return 0;
}

int StartNewGame(){

    ClearBoardMem(board);
    Start();
}


int Start(){

    board = MakeBoard();
    GetBoardFromSaves(board);

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
        TryMakeMove(board, inputDirection);
    }

    int boxSize = HEIGHT/(BOARD_SIZE+2);


    SDL_Surface * titleTextSurface = TTF_RenderText_Blended(titleFont,"TAQUIN",(SDL_Color){255,255,255,255});
    SDL_Texture * titleTextTexture = SDL_CreateTextureFromSurface(rend,titleTextSurface);
    SDL_RenderCopy(rend,titleTextTexture,NULL,
    &(SDL_Rect){
    WIDTH/2 - titleTextSurface->w/2,
    boxSize/2,
    titleTextSurface->w,
    titleTextSurface->h});

    int xStart = WIDTH/2  - (BOARD_SIZE * boxSize)/2;
    int yStart = HEIGHT/2 + (boxSize/2) - (BOARD_SIZE * boxSize)/2;

    for(int i =0; i< BOARD_SIZE; i++){
        for(int j =0; j< BOARD_SIZE; j++){
            SDL_Rect rect;
            rect.x = xStart + boxSize*i; rect.y = yStart + boxSize *j; rect.h = boxSize; rect.w = boxSize;
            RenderImage(rend,"UiBox.png",&rect);

            char numString[10];
            if(board[j][i]!= 0){
                sprintf(numString,"%d",board[j][i]);
            }
            else{
                sprintf(numString," ");
            }


            SDL_Surface * textSurface = TTF_RenderText_Blended(font,numString,(SDL_Color){255,255,255,255});
            SDL_Texture * textTexture = SDL_CreateTextureFromSurface(rend,textSurface);
            SDL_RenderCopy(rend,textTexture,NULL,
            &(SDL_Rect){
            xStart + boxSize*i + boxSize/2 - textSurface->w/2.5,
            yStart + boxSize *j+ boxSize/2 - textSurface->h/2.5,
            textSurface->w,
            textSurface->h});

        }
    }

    if(CheckIfWin(board)){
        if(CONSOLE_VERSION == 0){
            /* Draw to window and loop with delay*/
            SDL_RenderPresent(rend);
            SDL_Delay(1000/FPS);
        }
        system("clear");
        ConsoleDisplayBoard(board);
        DelayedPrint("========= You Won ! =========\n",20);
        Wait(2000);
        StartNewGame();
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

        TTF_Init();
        font = TTF_OpenFont(FONT_PATH,35);
        titleFont = TTF_OpenFont(FONT_PATH,80);
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
