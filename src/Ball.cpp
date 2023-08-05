#include "Ball.h"

Ball::Ball(Vec2 position, Vec2 velocity)
    : position(position), velocity(velocity)
  {
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
    rect.w = BALL_WIDTH;
    rect.h = BALL_HEIGHT;
  }


void Ball::Draw(SDL_Renderer* renderer) {
  rect.x = static_cast<int>(position.x);
  rect.y = static_cast<int>(position.y);

  SDL_RenderFillRect(renderer, &rect);
}

void Ball::Update(float deltatime) {
  position += velocity * deltatime;
}