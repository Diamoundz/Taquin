#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "game_tools.h"


// Compile Line : gcc -std=c17 main.c -I{.\SDL2\include} -L{.\SDL2\lib} -Wall  -lSDL2main -lSDL2 -o main

// Makefile line : make

#define WIDTH 640
#define HEIGHT 480
#define SIZE 20
#define SPEED 600
#define GRAVITY 60
#define FPS 60
#define JUMP -1200



int main(int argc, char* argv[]){
    /* Initializes the timer, audio, video, joystick,
    haptic, gamecontroller and events subsystems */
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 0;
    }
    /* Create a window */
    SDL_Window* wind = SDL_CreateWindow("Hello Platformer!",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        WIDTH, HEIGHT, 0);
    if (!wind)
    {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }
    /* Create a renderer */
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(wind, -1, render_flags);
    if (!rend)
    {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(wind);
        SDL_Quit();
        return 0;
    }
    /* Main loop */
    bool running = true, jump_pressed = false, can_jump = true,
                    left_pressed = false, right_pressed = false;
    SDL_Event event;


    srand(time(NULL));

    SDL_Rect * rectList = malloc(sizeof(SDL_Rect)*10);

    for(int i=0; i< 10; i++){
        SDL_Rect rect = {(int) 0, 0, SIZE, SIZE};
        rectList[i] = rect;
    }

    while (running)
    {
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
                    case SDL_SCANCODE_SPACE:
                        jump_pressed = true;
                        break;
                    case SDL_SCANCODE_A:
                    case SDL_SCANCODE_LEFT:
                        left_pressed = true;
                        break;
                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        right_pressed = true;
                        break;
                    default:
                        break;
                    }
                    break;
            case SDL_KEYUP:
                switch (event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_SPACE:
                        jump_pressed = false;
                        break;
                    case SDL_SCANCODE_A:
                    case SDL_SCANCODE_LEFT:
                        left_pressed = false;
                        break;
                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        right_pressed = false;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
        }
        /* Clear screen */
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);

        SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);

        /* Draw the rectangle */
        for(int i =0;i<10;i++){
            rectList[i].x = (WIDTH/10)*i;
            //rectList[i].y = (HEIGHT/2)-SIZE/2;
            int vel = GetRandomNumber(1);
            rectList[i].y += vel;
            SDL_RenderFillRect(rend, &rectList[i]);
        }


        /* Draw to window and loop */
        SDL_RenderPresent(rend);
        SDL_Delay(1000/FPS);
    }
    /* Release resources */
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(wind);
    SDL_Quit();
    return 0;
}

