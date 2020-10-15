#ifndef BoxColliderComponent_hpp
#define BoxColliderComponent_hpp

#include <string>
#include "SDL2/SDL.h"
#include "Components.hpp"

class BoxColliderComponent : public Component
{
public:
  SDL_Rect collider;
  std::string tag;

  TransformComponent *transform;

  BoxColliderComponent() = default;

  BoxColliderComponent(std::string t)
  {
    tag = t;
  }

  void init() override
  {
    // if (!entity->hasComponent<TransformComponent>())
    // {
    //   entity->addComponent<TransformComponent>();
    // }
    transform = &entity->getComponent<TransformComponent>();

    Game::colliders.push_back(this);
  }

  void update() override
  {
    collider.x = static_cast<int>(transform->position.x);
    collider.y = static_cast<int>(transform->position.y);
    collider.w = static_cast<int>(transform->width);
    collider.h = static_cast<int>(transform->height);
  }
};

#endif /* BoxColliderComponent */