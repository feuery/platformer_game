#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <utility>

#include <object_type.h>
/*
 * pelaajan spawn_point
 * kolikoton block
 * rautatiesilta
 * warp_start
 * warp_end
 * kolikollinen_block
 * rautapätkä_alku
 * rautapätkä_loppu
 * rautapätkä_väli
 * taskulamppuvartija
 * maaliblokki
 */

using namespace std;

class Game{
public:
  Game(int w, int h, const char* title);

  void RunFrame();
  bool initialized() const {
    return running;
  }

  ~Game();

  SDL_Surface* to_surface(const char* str);

private:

  //returns false on quit
  bool eventloop();
  void do_kbd_up(SDL_Event& e);

  void drawobjects();
  
  SDL_Window* window;
  SDL_Surface* window_surface;

  int W, H, camera_x, camera_y;
  bool running, dragging;

  Uint32 lastUpdated;

  TTF_Font *font;

  //level editor specific stuff
  object_type current_type = start;

  void draw_hud();

  vector<pair<int, int>> where_dragged;
};

#endif //GAME_H
