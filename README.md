# sdl2-demos

This repository is a series of demo projects to learn SDL2. SDL is written in C and works with C++ natively, these demos are written in C++.

## Compiling

After [installing SDL2](https://wiki.libsdl.org/Installation) compile and link the SDL2 library with the `-lSDL2` flag. E.g. `g++ main.cpp -o demo -lSDL2`

## Demos

### Empty Window

- A hello world of sorts for creating a window in SDL2. 
- Creates a window and destroys the window after 5 seconds.
- The window pointer is created from the return of [SDL_CreateWindow()](https://wiki.libsdl.org/SDL_CreateWindow).
