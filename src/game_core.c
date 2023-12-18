#include "definitions.h"
#include "game_tools.h"
#include "game_core.h"
#include "rendering_tools.h"

// Define booleans as global variables for ease of manipulation
bool running = true;
bool isWinState = false;
bool isAutomaticResolve = false;

// Keep track of the board
int **board = NULL;

#if CONSOLE_VERSION == 0

// Keep track of the window, the renderer, and the event fetcher as global variables
SDL_Window *wind = NULL;
SDL_Renderer *rend = NULL;
TTF_Font *font = NULL;
TTF_Font *titleFont = NULL;
TTF_Font *smallFont = NULL;

// Function to render an image on the screen
int RenderImage(SDL_Renderer *rend, char *imageName, SDL_Rect *rect) {
    // Check if the image name is valid
    if (strlen(imageName) <= 1) {
        return 0;
    }

    // Create the full path to the image
    char *pathName = malloc(sizeof(char) * (strlen(imageName) + strlen(SOURCE_PATH) + 1));
    pathName[0] = '\0';
    strcat(pathName, SOURCE_PATH);
    strcat(pathName, imageName);

    // Load the image
    SDL_Surface *image = IMG_Load(pathName);

    // Check if the image is loaded successfully
    if (image == NULL) {
        printf("Error: Failed to load image with path name %s - %s\n", pathName, SDL_GetError());
    }

    // Create a texture from the surface and render it
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, image);
    SDL_RenderCopy(rend, texture, NULL, rect);

    // Free resources
    SDL_FreeSurface(image);
    SDL_DestroyTexture(texture);
    free(pathName);
    return 0;
}

// Function to write text on the screen
int WriteText(SDL_Renderer *rend, char *text, SDL_Color color, TTF_Font *font, bool centered, SDL_Rect rect) {
    // Render the text to a surface
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text, color);

    // Adjust the position for centering
    rect.x -= ((centered) ? (textSurface->w / 2) : 0);
    rect.y -= ((centered) ? (textSurface->h / 2) : 0);
    rect.w = textSurface->w;
    rect.h = textSurface->h;

    // Create a texture from the surface and render it
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(rend, textSurface);
    SDL_RenderCopy(rend, textTexture, NULL, &rect);

    // Free resources
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    return 0;
}

// Function to display the board on the screen
int DisplayBoard(int **board, SDL_Renderer *rend, TTF_Font *font) {
    int boxSize = HEIGHT / (BOARD_SIZE + 2);
    int xStart = WIDTH / 2 - (BOARD_SIZE * boxSize) / 2;
    int yStart = HEIGHT / 2 + (boxSize / 4) - (BOARD_SIZE * boxSize) / 2;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            SDL_Rect rect;
            rect.x = xStart + boxSize * i;
            rect.y = yStart + boxSize * j;
            rect.h = boxSize;
            rect.w = boxSize;

            // Render the image for the board cell
            RenderImage(rend, "UiBox.png", &rect);

            char numString[10];
            if (board[j][i] != 0) {
                sprintf(numString, "%d", board[j][i]);
            } else {
                sprintf(numString, " ");
            }

            // Write the text on the board cell
            WriteText(rend, numString, (SDL_Color){255, 255, 255, 255}, font, true,
                      (SDL_Rect){xStart + boxSize * i + boxSize / 2, yStart + boxSize * j + boxSize / 2, 0, 0});
        }
    }
    return 0;
}

// Function to get events from the user input
int GetEvents() {
    SDL_Event event;
    // Process events
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
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
                    case SDL_SCANCODE_R:
                        return -2;
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

// Function to update the game state
int Update() {
    // Get events and input and refresh the screen
    ClearScreen(rend);

    int inputDirection = NO_DIR;

    if (!isAutomaticResolve) {
        inputDirection = GetEvents();
        if (inputDirection != NO_DIR) {
            if (inputDirection != -2) {
                TryMakeMove(board, inputDirection);
            } else {
                isAutomaticResolve = true;
            }
        }
    } else {
        TryMakeMove(board, GetResolutionMove(board));
    }

    int boxSize = HEIGHT / (BOARD_SIZE + 2);

    // Render the UI elements
    RenderImage(rend, "UiBorders.png", &(SDL_Rect){0, -25, WIDTH, HEIGHT});
    WriteText(rend, "TAQUIN", (SDL_Color){255, 255, 255, 255}, titleFont, true, (SDL_Rect){WIDTH / 2, boxSize / 1.2, 0, 0});
    WriteText(rend, "/ Press (ESC) to Quit /", (SDL_Color){255, 255, 255, 255}, smallFont,
              true, (SDL_Rect){WIDTH / 2, HEIGHT - boxSize / 3, 0, 0});

    if (!isWinState) {
        DisplayBoard(board, rend, font);
    } else {
        // Display winning message
        WriteText(rend, "YOU WON!", (SDL_Color){255, 255, 255, 255}, titleFont, true, (SDL_Rect){WIDTH / 2, HEIGHT / 2, 0, 0});
        SDL_RenderPresent(rend);
        Wait(2000);
        StartNewGame();
    }

    // Check for a win state
    if (!isWinState && CheckIfWin(board)) {
        system("clear");
        ConsoleDisplayBoard(board);
        if (CONSOLE_VERSION == 0) {
            isWinState = true;
        } else {
            DelayedPrint("========= You Won ! =========\n", 20);
        }
    }

    return 0;
}

#endif

// Function to stop the game and free resources
int Stop() {
#if CONSOLE_VERSION == 0
    DestroyWindow(wind, rend);
#endif
    ClearBoardMem(board);
    return 0;
}

// Function to start a new game
int StartNewGame() {
    isAutomaticResolve = false;
    isWinState = false;
    ClearBoardMem(board);
    Start();
    return 0;
}

// Function to start the game
int Start() {
    board = MakeBoard();
    GetBoardFromSaves(board);
    ConsoleDisplayBoard(board);
    return 0;
}

// Function to update the game state in the console version
int ConsoleUpdate() {
    int inputDirection = NO_DIR;

    if (!isAutomaticResolve) {
        inputDirection = GetConsoleInput();
        if (inputDirection != NO_DIR) {
            TryMakeMove(board, inputDirection);
        } else {
            isAutomaticResolve = true;
        }
    } else {
        TryMakeMove(board, GetResolutionMove(board));
    }

    // Check for a win state
    if (!isWinState && CheckIfWin(board)) {
        system("clear");
        ConsoleDisplayBoard(board);
        DelayedPrint("========= You Won ! =========\n", 20);
    }

    return 0;
}

// Function to initialize the game
int Awake() {
    srand(time(NULL));

#if CONSOLE_VERSION == 0
    // Initialize SDL and related subsystems
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 0;
    }

    wind = MakeWindow(WIDTH, HEIGHT);
    rend = MakeRenderer(wind);

    TTF_Init();
    font = TTF_OpenFont(FONT_PATH, 35);
    titleFont = TTF_OpenFont(FONT_PATH, 80);
    smallFont = TTF_OpenFont(FONT_PATH, 20);
#endif

    Start();

    while (running) {
#if CONSOLE_VERSION == 0
        Update();
        // Draw to window and loop with delay
        SDL_RenderPresent(rend);
        SDL_Delay(1000 / FPS);
#else
        ConsoleUpdate();
#endif
    }

    Stop();
    return 0;
}
