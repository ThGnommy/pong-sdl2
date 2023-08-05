#pragma once

#include <SDL2/SDL.h>
#include "Vec2.h"

extern const int WINDOW_HEIGHT;
extern const int WINDOW_WIDTH;

const int PADDLE_WIDTH = 10;
const int PADDLE_HEIGHT = 115;

class Paddle {

public:
  Paddle(Vec2 position, Vec2 velocity);

  void Draw(SDL_Renderer* renderer);
  void Update(float deltatime);

  Vec2 position;
  Vec2 velocity;
  SDL_Rect rect{};

};