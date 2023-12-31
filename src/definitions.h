#ifndef DEFINITIONS_INCLUDED
    #define DEFINITIONS_INCLUDED

    #define CONSOLE_VERSION 1
    #if CONSOLE_VERSION == 0
        #include <SDL2/SDL_ttf.h>
        #include <SDL2/SDL_image.h>
        #include <SDL2/SDL.h>
    #endif


    #define LEFT -1
    #define RIGHT 1
    #define UP 2
    #define DOWN 4
    #define NO_DIR 0

    #define WIDTH 1600
    #define HEIGHT 900

    #define TITLE_OFFSET 50;

    #define FPS 60

    #define SAVE_FILE "board_saves.txt"
    #define SOURCE_PATH "./ressources/"
    #define FONT_PATH "./ressources/font.ttf"

    #define BOARD_SIZE 4
    #define MIN_BOARD_SHUFFLE 55
    #define MAX_BOARD_SHUFFLE 70
    #define SAVED_BOARD_COUNT 30

    
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>
    #include <time.h>
    #include <string.h>


    #ifdef _WIN32
        #include <windows.h>
    #else
        #include <unistd.h>
    #endif

#endif
