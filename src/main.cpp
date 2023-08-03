#include <SDL2/SDL.h>

// windows dimensions
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main()
{

  // Initialize SDL components
  SDL_Init(SDL_INIT_VIDEO);


  SDL_Window* window = SDL_CreateWindow("Pong", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

  // Game logic

  bool running = true;

  // game loop
  while(running) {
    SDL_Event event;

    // watch if the user press the escape key
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        running = false;
      } else if(event.type == SDL_KEYDOWN) {
        if(event.key.keysym.sym == SDLK_ESCAPE) {
          running = false;
        }
      }
    }

    // set the renderer window to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    // clear
    SDL_RenderClear(renderer);

    // Update the screen with any rendering performed since the previous call.
    SDL_RenderPresent(renderer);

  }

  // Destroy all
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
