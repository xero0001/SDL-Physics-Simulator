#ifndef Collision_hpp
#define Collision_hpp

#include <string>
#include "SDL2/SDL.h"

class BoxColliderComponent;

class Collision
{
public:
  static bool AABB(const SDL_Rect &recA, const SDL_Rect &recB);
  static bool AABB(const BoxColliderComponent &colA, const BoxColliderComponent &colB);
};

#endif /* Collision_hpp */