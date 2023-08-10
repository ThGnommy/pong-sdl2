#pragma once

#include <SDL2/SDL.h>
#include "Vec2.h"

const int BALL_WIDTH = 15;
const int BALL_HEIGHT = 15;

enum class CollisionType {
  None, 
  Top,
  Middle,
  Bottom,
  Left, 
  Right
};

struct Contact {
  CollisionType type;
  float penetration;
};

class Ball {
public:
  Ball(Vec2 position, Vec2 velocity);

  Vec2 position;
  Vec2 velocity;
  SDL_Rect rect{};

  void Draw(SDL_Renderer* renderer);
  void Update(float deltatime);
  void CollideWithPaddle(Contact const& contact);
  void CollideWithWalls(Contact const& contact);
};