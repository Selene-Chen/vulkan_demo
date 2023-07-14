
#include <SDL.h>

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

  while (!should_closed) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        should_closed = true;
      }
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
