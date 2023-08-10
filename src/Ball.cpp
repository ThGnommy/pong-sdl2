#include "Ball.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
float const BALL_SPEED = 0.5f;

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

void Ball::CollideWithPaddle(Contact const& contact) {
  position.x += contact.penetration;
  velocity.x = -velocity.x;

  if (contact.type == CollisionType::Top)
  {
    velocity.y = -.75 * BALL_SPEED;
  } 
  else if (contact.type == CollisionType::Bottom)
  {
    velocity.y = 0.75 * BALL_SPEED;
  }
}

void Ball::CollideWithWalls(Contact const & contact)
{
  		if ((contact.type == CollisionType::Top)
		    || (contact.type == CollisionType::Bottom))
		{
			position.y += contact.penetration;
			velocity.y = -velocity.y;
		}
		else if (contact.type == CollisionType::Left)
		{
			position.x = WINDOW_WIDTH / 2.0f;
			position.y = WINDOW_HEIGHT / 2.0f;
			velocity.x = BALL_SPEED;
			velocity.y = 0.75f * BALL_SPEED;
		}
		else if (contact.type == CollisionType::Right)
		{
			position.x = WINDOW_WIDTH / 2.0f;
			position.y = WINDOW_HEIGHT / 2.0f;
			velocity.x = -BALL_SPEED;
			velocity.y = 0.75f * BALL_SPEED;
		}
}