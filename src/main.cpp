#include "../include/game.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <bitset>
#include <cstdint>
#include <cstdio>

int main(int argc, char *argv[]) {
  // if (SDL_Init(SDL_INIT_VIDEO) != 0) {
  //   return 1;
  // }
  //
  // SDL_Window *win = SDL_CreateWindow("SDL2 Window", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
  // if (!win) {
  //   // std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
  //   perror("sdl SDL_CreateWindow error");
  //   SDL_Quit();
  //   return 1;
  // }
  //
  // SDL_Surface *winSurface = SDL_GetWindowSurface(win);
  //
  // SDL_FillRect(winSurface, NULL, SDL_MapRGB(winSurface->format, 255, 90, 120));
  //
  // SDL_UpdateWindowSurface(win);
  // SDL_Delay(2500);
  //
  // SDL_DestroyWindow(win);
  // SDL_Quit();

  Board b{};

  while (true) {
    string dir = "a";
    cin >> dir;

    if (dir == "c") {
      b.rotate_block(Block::RotateDirection::C);
      // cout << "[" << b.current.width << ", " << b.current.height << "]" << endl;
    } else if (dir == "cc") {
      b.rotate_block(Block::RotateDirection::C);
    } else if (dir == "l") {
      b.move_block(Block::ShiftDirection::Left);
    } else if (dir == "r") {
      b.move_block(Block::ShiftDirection::Right);
    } else if (dir == "d") {
      b.move_block(Block::ShiftDirection::Down);
    } else if (dir == "s") {
      b.drop_block();
      b.current.display();
    }

    b.display();
  }
}
