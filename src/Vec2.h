#pragma once

class Vec2 {

public:
  Vec2()
    : x(0.0), y(0.0) 
  {}

  Vec2(float x, float y)
    : x(x), y(y)
  {}

  Vec2 operator+(Vec2 const& rhs) {
    return Vec2(x + rhs.x, y + rhs.y);
  }

  Vec2& operator+=(Vec2 const& rhs) {
    x += rhs.x;
    y += rhs.y;

    return *this;
  }

  Vec2 operator*(float rhs) {
    return Vec2(x * rhs, y * rhs);
  }

  float x, y;

};