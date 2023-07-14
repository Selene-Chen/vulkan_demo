#include <SDL.h>

#include <toy2d/toy2d.hpp>

constexpr int WindowWidth = 1024;
constexpr int WindowHeight = 720;

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Window *window = SDL_CreateWindow(
    "sanbox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth,
    WindowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);

  if (!window) {
    SDL_Log("create window failed!");
    exit(2);
  }

  bool should_closed = false;
  SDL_Event event;

  toy2d::Init();

  while (!should_closed) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        should_closed = true;
      }
    }
  }

  toy2d::Quit();
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
