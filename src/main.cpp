#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Vec2.h"
#include "Ball.h"
#include "Paddle.h"
#include "PlayerScore.h"

// windows dimensions
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main()
{

  // Initialize SDL components
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  SDL_Window* window = SDL_CreateWindow("Pong", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

  // Initialize the font
  TTF_Font* scoreFont = TTF_OpenFont("./fonts/Minecraft-font.ttf", 40);

  // Create the ball
  Ball ball(
    Vec2((WINDOW_WIDTH / 2.0) - (BALL_WIDTH / 2.0), 
    (WINDOW_HEIGHT / 2.0f) - (BALL_WIDTH / 2.0f))
  );

  // Create paddles
  Paddle paddleOne(
    Vec2(50.0, (WINDOW_HEIGHT / 2.0) - (PADDLE_HEIGHT / 2.0))
  );
  
  Paddle paddleTwo(
    Vec2((WINDOW_WIDTH - 50.0 - PADDLE_WIDTH), (WINDOW_HEIGHT / 2.0) - (PADDLE_HEIGHT / 2.0))
  );

  // Create the player score text fields
  Vec2 scoreOnePosition = Vec2(WINDOW_WIDTH / 4, 20);
  PlayerScore playerOneScoreText(scoreOnePosition, renderer, scoreFont);

  Vec2 scoreTwoPosition = Vec2(3 * WINDOW_WIDTH / 4, 20);
  PlayerScore playerTwoScoreText(scoreTwoPosition, renderer, scoreFont);

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

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for(int y = 0; y < WINDOW_HEIGHT; y++) {
      if(y % 5) {
        SDL_RenderDrawPoint(renderer, WINDOW_WIDTH / 2, y);
      }
    }

    // Draw the ball
    ball.Draw(renderer);

    // Draw the paddles
    paddleOne.Draw(renderer);
    paddleTwo.Draw(renderer);

    // Display the scores
    playerOneScoreText.Draw();
    playerTwoScoreText.Draw();

    // Present the backbuffer
    SDL_RenderPresent(renderer);

  }

  // Cleanup
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  // Clear fonts
  TTF_CloseFont(scoreFont);
  TTF_Quit();
  SDL_Quit();

  return 0;
}
