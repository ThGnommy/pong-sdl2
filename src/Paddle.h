#pragma once

#include <SDL2/SDL.h>
#include "Vec2.h"

const int PADDLE_WIDTH = 10;
const int PADDLE_HEIGHT = 115;

class Paddle {

public:
  Paddle(Vec2 position);

  Vec2 position;
  SDL_Rect rect{};

  void Draw(SDL_Renderer* renderer);

};