#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <vector>

class BoxColliderComponent;

class Game
{
public:
  // static int mouseX;
  // static int mouseY;

  Game();
  ~Game();
  void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

  void handleEvents();
  void update();
  bool running() { return isRunning; };
  void render();
  void clean();

  // static void AddTile(int id, int x, int y);
  static void AddBox(float x, float y);
  static SDL_Renderer *renderer;
  static SDL_Event event;
  static std::vector<BoxColliderComponent *> colliders;

private:
  int cnt = 0;
  int width = 800;
  int height = 640;

  bool pressed = false;
  bool isRunning = false;
  SDL_Window *window;
};

#endif /* Game_hpp */