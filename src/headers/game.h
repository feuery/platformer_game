#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <utility>

using namespace std;

class Game{
public:
  Game(int w, int h, const char* title);

  void RunFrame();
  bool initialized() const {
    return running;
  }

  ~Game();

private:

  //returns false on quit
  bool eventloop();

  void drawobjects();
  
  SDL_Window* window;
  SDL_Surface* window_surface;

  int W, H, camera_x, camera_y;
  bool running, dragging;

  Uint32 lastUpdated;

  TTF_Font *font;

  vector<pair<int, int>> where_dragged;
};

#endif //GAME_H
