#ifndef PhysicsBoxComponent_hpp
#define PhysicsBoxComponent_hpp

#include "SDL2/SDL.h"
#include "Components.hpp"
#include "../Vector2D.hpp"

class PhysicsBoxComponent : public Component
{
public:
  TransformComponent *transform;
  SDL_Rect destRect;
  Vector2D velocity;

  PhysicsBoxComponent() = default;
  ~PhysicsBoxComponent() = default;

  PhysicsBoxComponent(float x, float y, int width, int height)
  {
    destRect.x = x;
    destRect.y = y;
    destRect.w = width;
    destRect.h = height;
  }

  void init() override
  {
    entity->addComponent<TransformComponent>((float)destRect.x, (float)destRect.y, destRect.w, destRect.h, 1);
    transform = &entity->getComponent<TransformComponent>();

    entity->addComponent<BoxColliderComponent>("1");
  }

  void update() override
  {
    transform->velocity.y += 0.2f;
    transform->position += transform->velocity;
  }

  void draw() override
  {
    destRect.x = transform->position.x;
    destRect.y = transform->position.y;
    destRect.w = transform->width;
    destRect.h = transform->height;

    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Game::renderer, &destRect);
  }
};

#endif /* PhysicsBoxComponent_hpp */