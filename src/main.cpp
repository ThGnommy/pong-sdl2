#include <iostream>
#include <chrono>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "Vec2.h"
#include "Ball.h"
#include "Paddle.h"
#include "PlayerScore.h"


// windows dimensions
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

enum Buttons {
  PaddleOneUp = 0,
  PaddleOneDown,
  PaddleTwoUp,
  PaddleTwoDown
};

const float PADDLE_SPEED = 1.0;
float const BALL_SPEED = 0.5f;


Contact CheckPaddleCollision(Ball const& ball, Paddle const& paddle) {
	float ballLeft = ball.position.x;
	float ballRight = ball.position.x + BALL_WIDTH;
	float ballTop = ball.position.y;
	float ballBottom = ball.position.y + BALL_HEIGHT;

	float paddleLeft = paddle.position.x;
	float paddleRight = paddle.position.x + PADDLE_WIDTH;
	float paddleTop = paddle.position.y;
	float paddleBottom = paddle.position.y + PADDLE_HEIGHT;

  Contact contact{};

	if (ballLeft >= paddleRight)
	{
		return contact;
	}

	if (ballRight <= paddleLeft)
	{
		return contact;
	}

	if (ballTop >= paddleBottom)
	{
		return contact;
	}

	if (ballBottom <= paddleTop)
	{
		return contact;
	}

  float paddleRangeUpper = paddleBottom - (2.0 * PADDLE_HEIGHT / 3.0);
  float paddleRangeMiddle = paddleBottom - (PADDLE_HEIGHT / 3.0);

  if (ball.velocity.x < 0) {
    // left paddle
    contact.penetration = paddleRight - ballLeft;
  } else if (ball.velocity.x > 0) {
    // right paddle
    contact.penetration = paddleLeft - ballRight;
  }

  if ((ballBottom > paddleTop) && (ballBottom < paddleRangeUpper)) {
    contact.type = CollisionType::Top;
  } else if ((ballBottom > paddleRangeUpper) && (ballBottom < paddleRangeMiddle)) {
    contact.type = CollisionType::Middle;
  } else {
    contact.type = CollisionType::Bottom;
  }

	return contact;
}

Contact CheckWallCollision(Ball const& ball)
{
	float ballLeft = ball.position.x;
	float ballRight = ball.position.x + BALL_WIDTH;
	float ballTop = ball.position.y;
	float ballBottom = ball.position.y + BALL_HEIGHT;

	Contact contact{};

	if (ballLeft < 0.0f)
	{
		contact.type = CollisionType::Left;
	}
	else if (ballRight > WINDOW_WIDTH)
	{
		contact.type = CollisionType::Right;
	}
	else if (ballTop < 0.0f)
	{
		contact.type = CollisionType::Top;
		contact.penetration = -ballTop;
	}
	else if (ballBottom > WINDOW_HEIGHT)
	{
		contact.type = CollisionType::Bottom;
		contact.penetration = WINDOW_HEIGHT - ballBottom;
	}

	return contact;
}

int main()
{
  // Initialize SDL components
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  // we don't need 44100
  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 1, 2048);

  SDL_Window* window = SDL_CreateWindow("Pong", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

  // Initialize the font
  TTF_Font* scoreFont = TTF_OpenFont("./fonts/Minecraft-font.ttf", 40);

  // Create the ball
  Ball ball(
    Vec2((WINDOW_WIDTH / 2.0) - (BALL_WIDTH / 2.0),  (WINDOW_HEIGHT / 2.0f) - (BALL_WIDTH / 2.0f)),
    Vec2(BALL_SPEED, 0.0)
  );

  // Create paddles
  Paddle paddleOne(
    Vec2(50.0, (WINDOW_HEIGHT / 2.0) - (PADDLE_HEIGHT / 2.0)),
    Vec2(0.0, 0.0)
  );


  Paddle paddleTwo(
    Vec2((WINDOW_WIDTH - 50.0 - PADDLE_WIDTH), (WINDOW_HEIGHT / 2.0) - (PADDLE_HEIGHT / 2.0)),
    Vec2(0.0, 0.0)
  );

  // Create the player score text fields
  Vec2 scoreOnePosition = Vec2(WINDOW_WIDTH / 4, 20);
  PlayerScore playerOneScoreText(scoreOnePosition, renderer, scoreFont);

  Vec2 scoreTwoPosition = Vec2(3 * WINDOW_WIDTH / 4, 20);
  PlayerScore playerTwoScoreText(scoreTwoPosition, renderer, scoreFont);

  // Inizialize sound effects
  Mix_Chunk* wallHitSound = Mix_LoadWAV("/sounds/sfx_wall_hit.wav");
  Mix_Chunk* paddleHitSound = Mix_LoadWAV("/sounds/sfx_paddle_hit.wav");

  // Game logic

  bool buttons[4] = {};

  int playerOneScore = 0;
  int playerTwoScore = 0;

  bool running = true;
  float deltatime = 0.0f;

  /*
    game loop 👇
  */

  while(running) {

    auto startTime = std::chrono::high_resolution_clock::now();

    SDL_Event event;

    // watch if the user press the escape key
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        running = false;
      } 
      else if(event.type == SDL_KEYDOWN) 
      {
        if(event.key.keysym.sym == SDLK_ESCAPE) {
          running = false;
        }

        if(event.key.keysym.sym == SDLK_w)
          buttons[Buttons::PaddleOneUp] = true;  
        else if(event.key.keysym.sym == SDLK_s)
          buttons[Buttons::PaddleOneDown] = true;
        else if(event.key.keysym.sym == SDLK_UP)
          buttons[Buttons::PaddleTwoUp] = true;
        else if(event.key.keysym.sym == SDLK_DOWN)
          buttons[Buttons::PaddleTwoDown] = true;
      }
      else if (event.type == SDL_KEYUP)
      {
        if(event.key.keysym.sym == SDLK_w)
          buttons[Buttons::PaddleOneUp] = false;  
        else if(event.key.keysym.sym == SDLK_s)
          buttons[Buttons::PaddleOneDown] = false;
        else if(event.key.keysym.sym == SDLK_UP)
          buttons[Buttons::PaddleTwoUp] = false;
        else if(event.key.keysym.sym == SDLK_DOWN)
          buttons[Buttons::PaddleTwoDown] = false;
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


    // handle keys

    if (buttons[Buttons::PaddleOneUp])
    {
      paddleOne.velocity.y = -PADDLE_SPEED;
    }
    else if (buttons[Buttons::PaddleOneDown])
    {
      paddleOne.velocity.y = PADDLE_SPEED;
    }
    else
    {
      paddleOne.velocity.y = 0.0f;
    }

    if (buttons[Buttons::PaddleTwoUp])
    {
      paddleTwo.velocity.y = -PADDLE_SPEED;
    }
    else if (buttons[Buttons::PaddleTwoDown])
    {
      paddleTwo.velocity.y = PADDLE_SPEED;
    }
    else
    {
      paddleTwo.velocity.y = 0.0f;
    }

    // Update the paddle positions
    paddleOne.Update(deltatime);
    paddleTwo.Update(deltatime);

    // check for collisions
    Contact contact = CheckPaddleCollision(ball, paddleOne);
    if (contact.type != CollisionType::None) {
      ball.CollideWithPaddle(contact);
      Mix_PlayChannel(-1, paddleHitSound, 0);
    } 
    else if (contact = CheckPaddleCollision(ball, paddleTwo);
      contact.type != CollisionType::None) {
        ball.CollideWithPaddle(contact);
        Mix_PlayChannel(-1, paddleHitSound, 0);
    }
    else if (contact = CheckWallCollision(ball);
    contact.type != CollisionType::None)
    {
      ball.CollideWithWalls(contact);

      if (contact.type == CollisionType::Left)
      {
        ++playerTwoScore;

        playerTwoScoreText.SetScore(playerTwoScore);
      }
      else if (contact.type == CollisionType::Right)
      {
        ++playerOneScore;

        playerOneScoreText.SetScore(playerOneScore);
      }
      else {
        Mix_PlayChannel(-1, wallHitSound, 0);
      }
    }


    // Update the ball position
    ball.Update(deltatime);

    // Present the backbuffer
    SDL_RenderPresent(renderer);

    // Calculate frame time
    auto stopTime = std::chrono::high_resolution_clock::now();
    deltatime = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
  }

  // Cleanup
  Mix_FreeChunk(wallHitSound);
  Mix_FreeChunk(paddleHitSound);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  // Clear fonts
  TTF_CloseFont(scoreFont);
  Mix_Quit();
  TTF_Quit();
  SDL_Quit();

  return 0;
}
