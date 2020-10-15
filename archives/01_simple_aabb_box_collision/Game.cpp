#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

Manager manager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<BoxColliderComponent *> Game::colliders;

enum groupLabels : std::size_t
{
  groupPhysics,
};

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
  // Bit flag
  int flags = 0;
  if (fullscreen == true)
  {
    flags |= SDL_WINDOW_FULLSCREEN;
  }

  // Save windo information
  this->width = width;
  this->height = height;

  // Check if Initialize successful
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
  {
    std::cout << "Subsystems Initialized" << std::endl;

    // Create and check window
    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (window)
    {
      std::cout << "Window created!" << std::endl;
    }
    else
    {
      std::cout << "Window creation failed" << std::endl;
    }

    // Create and check renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer)
    {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      std::cout << "Renderer created!" << std::endl;
    }
    else
    {
      std::cout << "Rendere creation failed" << std::endl;
    }

    isRunning = true;
  }
  else
  {
    isRunning = false;
  }

  // Check SDL_image
  // if (!IMG_Init(IMG_INIT_PNG))
  // {
  //   std::cout << "SDL_image could not initialize! SDL_image Error:" << std::endl
  //             << IMG_GetError() << std::endl;
  //   isRunning = false;
  // }
  // else
  // {
  //   std::cout << "SDL_image initialized!" << std::endl;
  // }

  // ECS implementation
  Game::AddBox(400.0f, 100.0f);
}

void Game::handleEvents()
{
  // SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type)
  {
  case SDL_QUIT:
    isRunning = false;
    break;
  case SDL_MOUSEBUTTONDOWN:
    if (pressed == false)
    {
      pressed = true;
      int mouseX;
      int mouseY;
      SDL_GetMouseState(&mouseX, &mouseY);
      Game::AddBox((float)mouseX, (float)mouseY);
    }
    break;
  case SDL_MOUSEBUTTONUP:
    if (pressed == true)
    {
      pressed = false;
    }
    break;
  default:
    break;
  }
}

void Game::update()
{
  manager.refresh();
  manager.update();

  for (auto c1 = colliders.begin(); c1 != colliders.end(); ++c1)
  {
    for (auto c2 = c1 + 1; c2 != colliders.end(); ++c2)
    {
      if (Collision::AABB(*(*c1), *(*c2)))
      {
        (*c2)->transform->position.y = (*c1)->transform->position.y - 32.0f;
        (*c2)->collider.y = (*c2)->transform->position.y;
        (*c2)->transform->velocity.y = 0.0f;
      }
    }
  }

  for (auto cc : colliders)
  {
    if (cc->collider.y + cc->collider.h > height)
    {
      cc->transform->position.y = height - 32.0f;
      cc->transform->velocity.y = 0.0f;
    }
  }
}

auto &physics(manager.getGroup(groupPhysics));

void Game::render()
{
  SDL_RenderClear(renderer);

  int i = 0;
  for (auto &t : physics)
  {
    i++;
    t->draw();
  }

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderPresent(renderer);
}

void Game::clean()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  std::cout << "Game Cleaned" << std::endl;
}

void Game::AddBox(float x, float y)
{
  auto &box(manager.addEntity());
  box.addComponent<PhysicsBoxComponent>(x, y, 32, 32);
  box.addGroup(groupPhysics);
}