#include "definitions.h"
#include "rendering_tools.h"
#include "game_tools.h"
#include "game_core.h"

//define booleans as global variables for ease of manipulation
bool running = true;
bool isWinState = false;

//keep track of the board
int ** board = NULL;

//keep track of the window, the renderer and the event fetcher as global variables
SDL_Window* wind= NULL;
SDL_Renderer* rend = NULL;
TTF_Font* font = NULL;
TTF_Font* titleFont = NULL;
TTF_Font* smallFont = NULL;


int RenderImage(SDL_Renderer * rend,char * imageName, SDL_Rect * rect){
    if(strlen(imageName)<=1){
        return 0;
    }
    char * pathName = malloc(sizeof(char)*(strlen(imageName)+strlen(SOURCE_PATH)+1));
    pathName[0] = '\0';

    strcat(pathName,SOURCE_PATH);
    strcat(pathName,imageName);

    SDL_Surface * image = IMG_Load(pathName);

    if(image == NULL){
        printf("Error : Failed to load image with path name %s - %s\n",pathName,SDL_GetError());
    }

    SDL_Texture * texture = SDL_CreateTextureFromSurface(rend,image);
    SDL_RenderCopy(rend, texture, NULL, rect);

    SDL_FreeSurface(image);
    SDL_DestroyTexture(texture);
    free(pathName);
    return 0;
}

int WriteText(SDL_Renderer * rend, char * text, SDL_Color color, TTF_Font * font,bool centered, SDL_Rect rect){


    SDL_Surface * textSurface = TTF_RenderText_Blended(font,text,color);

    rect.x -= ((centered)? (textSurface->w/2):0);
    rect.y -= ((centered)? (textSurface->h/2):0);
    rect.w = textSurface->w;
    rect.h = textSurface->h;

    SDL_Texture * textTexture = SDL_CreateTextureFromSurface(rend,textSurface);
    SDL_RenderCopy(rend,textTexture,NULL,&rect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    return 0;
}

int DisplayBoard(int ** board, SDL_Renderer * rend, TTF_Font * font){
    int boxSize = HEIGHT/(BOARD_SIZE+2);
    int xStart = WIDTH/2  - (BOARD_SIZE * boxSize)/2;
    int yStart = HEIGHT/2 + (boxSize/4) - (BOARD_SIZE * boxSize)/2;

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

            WriteText(rend,numString,(SDL_Color){255,255,255,255},font,true,(SDL_Rect){xStart + boxSize*i + boxSize/2,yStart + boxSize *j+ boxSize/2,0,0});

        }
    }
    return 0;
}

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
    isWinState = false;
    ClearBoardMem(board);
    Start();
    return 0;
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

    if(CONSOLE_VERSION == 0){

        RenderImage(rend,"UiBorders.png",&(SDL_Rect){0,-25,WIDTH,HEIGHT});
        WriteText(rend,"TAQUIN",(SDL_Color){255,255,255,255},titleFont,true,(SDL_Rect){WIDTH/2,boxSize/1.2,0,0});

        WriteText(rend,"/ Press (ESC) to Quit /",(SDL_Color){255,255,255,255},smallFont,true,(SDL_Rect){WIDTH/2,HEIGHT-boxSize/3,0,0});


        if(!isWinState){
            DisplayBoard(board,rend,font);
        }
        else{
            WriteText(rend,"YOU WON!",(SDL_Color){255,255,255,255},titleFont,true,(SDL_Rect){WIDTH/2,HEIGHT/2,0,0});
            SDL_RenderPresent(rend);
            Wait(2000);
            StartNewGame();
        }

    }
    if(!isWinState && CheckIfWin(board)){
        system("clear");
        ConsoleDisplayBoard(board);
        if(CONSOLE_VERSION == 0){
            isWinState = true;
        }
        else{
            DelayedPrint("========= You Won ! =========\n",20);
        }
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
        smallFont = TTF_OpenFont(FONT_PATH,20);
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
    return 0;
}
