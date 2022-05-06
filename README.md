# sdl2-demos

This repository is a series of demo projects to learn SDL2. SDL is written in C and works with C++ natively, these demos are written in C++.

## Compiling

After [installing SDL2](https://wiki.libsdl.org/Installation) compile and link the SDL2 library with the `-lSDL2` flag. E.g. `g++ main.cpp -o demo -lSDL2`. These demos were written on a Linux system, if compiling on Mac or Windows you may need to adjust the SDL2 library includes from `#include "SDL2/SDL.h"` to `#include "SDL.h"`.

## Demos

### Empty Window

- A hello world of sorts for creating a window in SDL2. 
- Creates a window and destroys the window after 5 seconds.
- The window pointer is created from the return of [SDL_CreateWindow()](https://wiki.libsdl.org/SDL_CreateWindow).

### Simple Events

- Uses the [SDL_PollEvent](https://wiki.libsdl.org/SDL_PollEvent) queue to log keyboard presses and mouse movements.
- Prints to the console the name of the key pressed, the coordinates of the mouse movement, or quits the application when the window close button is pressed.

### Simple Surface

- Uses [SDL_GetWindowSurface](https://wiki.libsdl.org/SDL_GetWindowSurface) and [SDL_BlitSurface](https://wiki.libsdl.org/SDL_BlitSurface) to apply .bmp images to the window.
- Cycle through 5 images with the spacebar.

### Simple Renderer

- Renders 3 filled rectangles and 3 drawn rectangles to the window 
- Add lines of random colors at random locations with the spacebar. 
- The delete key clears the window with the last color set to the renderer.
- [SDL_CreateRenderer](https://wiki.libsdl.org/SDL_CreateRenderer) returns a context to render 2D graphics for a window.
