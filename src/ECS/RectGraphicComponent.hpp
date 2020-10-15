#ifndef RectGraphicComponent_hpp
#define RectGraphicComponent_hpp

#include "Components.hpp"
#include "SDL2/SDL.h"

class RectGraphicComponent : public Component
{
private:
  TransformComponent *transform;
  SDL_Rect destRect;

public:
  RectGraphicComponent() = default;
  ~RectGraphicComponent() = default;

  void init() override
  {
    transform = &entity->getComponent<TransformComponent>();

    destRect.x = transform->position.x;
    destRect.y = transform->position.y;
    destRect.w = transform->width;
    destRect.h = transform->height;
  }

  void update() override
  {
    destRect.x = static_cast<int>(transform->position.x);
    destRect.y = static_cast<int>(transform->position.y);
    destRect.w = static_cast<int>(transform->width);
    destRect.h = static_cast<int>(transform->height);
  }

  void draw() override
  {
    SDL_RenderDrawRect(Game::renderer, &destRect);
  }
};

#endif /* RectGraphicComponent_hpp */