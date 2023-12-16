# Taquin Game

This is a simple implementation of the Taquin game using SDL (Simple DirectMedia Layer) for graphics rendering. The game allows you to play the Taquin puzzle, also known as the 15-puzzle, where you need to arrange numbers in ascending order by sliding tiles into an empty space.

## Table of Contents
- [Architecture](#architecture)
- [Makefile](#makefile)
- [Header Files](#header-files)
- [SDL](#sdl)

### Architecture


### Makefile

The provided Makefile compiles the Taquin game. It includes rules for compiling object files, linking, and cleaning the project, available for Windows as well as Linux.

```make WINDOWS
# command : mingw32-make -f MakefileWindows
CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -I./SDL2/include 
LDFLAGS :=  -L./SDL2/lib -lSDL2 -L./SDL2_ttf/lib -lSDL2_ttf -L./SDL2_image/lib -lSDL2_image

SRC_FILES := src/main.c src/game_core.c src/game_tools.c src/rendering_tools.c
OBJ_FILES := $(SRC_FILES:.c=.o)
EXECUTABLE := Taquin_Windows.exe

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	del /Q src\main.o src\game_core.o src\game_tools.o src\rendering_tools.o $(EXECUTABLE)
```

```make LINUX
# When using this makefile make sure to first install the SDL2,SDL2_ttf and SDL2_image libraries on your GNU
CC := gcc
CFLAGS := -Wall -Wextra -std=c99
LDFLAGS := -lSDL2 -lSDL2_image -lSDL2_ttf

SRC_FILES := src/main.c src/game_core.c src/game_tools.c src/rendering_tools.c
OBJ_FILES := $(SRC_FILES:.c=.o)
EXECUTABLE := Taquin_GNU_exe

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ_FILES) $(EXECUTABLE)
```


### SDL

SDL (Simple DirectMedia Layer) is used for graphics rendering in the game. It provides functions for creating windows, rendering images, and handling events.

Make sure to install the required SDL libraries (`SDL2`, `SDL2_ttf`, `SDL2_image`) before compiling the game if you are using Linux. You can find SDL installation instructions for your platform on the official SDL website.

```bash
# Install SDL2
# Example for Ubuntu/Linux
sudo apt-get install libsdl2-dev

# Install SDL2_ttf
sudo apt-get install libsdl2-ttf-dev

# Install SDL2_image
sudo apt-get install libsdl2-image-dev
```