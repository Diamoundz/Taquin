# Taquin Game

This is a simple implementation of the Taquin game using SDL (Simple DirectMedia Layer) for graphics rendering. The game allows you to play the Taquin puzzle, also known as the 15-puzzle, where you need to arrange numbers in ascending order by sliding tiles into an empty space.

## Table of Contents
- [Architecture](#architecture)
- [Makefile](#makefile)
- [SDL](#sdl)

### Architecture

#### Sole Header Files

1. **definitions.h**
   - Centralized location for constants, macros, and includes necessary libraries.
   - Defines directions, board dimensions, file paths, and includes standard and SDL libraries.

#### Source Files

1. **main.c**
   - Entry point of the program.
   - Calls the `Awake` function to initialize the game environment and enters the main game loop.

2. **game_core.c**
   - Implements functions for core game logic.
   - Checks for win conditions, handles moves, and initializes the game board.

3. **game_tools.c**
   - Implements utility functions for the game.
   - Creates and clears the game board, shuffles the board, and serializes/deserializes game states.

4. **rendering_tools.c**
   - Implements functions for rendering images and text using SDL.


#### Overall Flow

1. **Initialization:**
   - Constants and macros are defined in `definitions.h`.
   - SDL and other libraries are included.

2. **Game Logic:**
   - Core game logic is implemented in `game_core.c`.

3. **Utility Functions:**
   - Utility functions for board manipulation, serialization, and shuffling are in `game_tools.c`.

4. **Rendering:**
   - Rendering functions using SDL are in `rendering_tools.c`.

5. **Main Loop:**
   - The `main.c` file orchestrates the main game loop.
   - Calls functions for initialization, updating the game state, handling events, and rendering.

6. **Makefile:**
   - Contains rules for compiling the project, creating object files, linking dependencies, and cleaning up.

#### Note:

- The code follows a modular structure, separating concerns into different files.
- The use of header files helps organize declarations and definitions, promoting code readability.
- SDL is used for graphics rendering and user input handling.
- The Makefile simplifies the compilation and build process.

This structure helps in maintaining code readability, reusability, and scalability.

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