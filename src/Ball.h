#pragma once

#include <SDL2/SDL.h>
#include "Vec2.h"

const int BALL_WIDTH = 15;
const int BALL_HEIGHT = 15;

class Ball {

public:
  Ball(Vec2 position, Vec2 velocity);

  Vec2 position;
  Vec2 velocity;
  SDL_Rect rect{};

  void Draw(SDL_Renderer* renderer);
  void Update(float deltatime);
};