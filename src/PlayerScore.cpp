#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "PlayerScore.h"

PlayerScore::PlayerScore(Vec2 position, SDL_Renderer* renderer, TTF_Font* font)
  : renderer(renderer), font(font)
{
  surface = TTF_RenderText_Solid(font, "0", {255, 255, 255, 255});
  texture = SDL_CreateTextureFromSurface(renderer, surface);

  int width;
  int height;

  SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

  rect.x = static_cast<int>(position.x);
  rect.y = static_cast<int>(position.y);
  rect.w = width;
  rect.h = height;
}

PlayerScore::~PlayerScore() {
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}

void PlayerScore::Draw() {
  SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

/*
  Essentially, SDL2 writes the (white) text onto an SDL_Surface and then
  creates a texture from that surface which is what is actually drawn
  to the screen.
*/