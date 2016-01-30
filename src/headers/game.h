#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <utility>

#include <object_type.h>
#include <object.h>

/*
 * pelaajan spawn_point
 * - Vakiokokoinen
 * kolikoton block
 * - Vakiokokoinen
 * rautatiesilta
 * - Vakiokokoinen
 * - millä frameilla törmäys tappaa?
 * warp_start
 * - Vakiokokoinen
 * - ID:n perusteella määrätään mikä johtaa mihinkin
 * warp_end
 * - Vakiokokoinen
 * - ID:n perusteella määrätään mikä johtaa mihinkin
 * kolikollinen_block
 * - Vakiokokoinen
 * - Aina 5 coinia
 * rautapätkä_alku
 * - Vakiokokoinen
 * rautapätkä_loppu
 * - Vakiokokoinen
 * rautapätkä_väli
 * - Vakiokokoinen
 * taskulamppuvartija
 * - Vakiokokoinen
 * maaliblokki
 * - Vakiokokoinen
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

  vector<Object*> to_clear;
};

#endif //GAME_H
