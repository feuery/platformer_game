#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <utility>
#include <queue>
#include <string>

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

  void Clear();

  ~Game();

  SDL_Surface* to_surface(const char* str);

private:

  //returns false on quit
  bool eventloop();
  void do_kbd_up(SDL_Event& e);
  void do_kbd_down(SDL_Event& e);

  void place_narrow_object(int x, int y);
  void place_wide_object(int x, int y);

  void drawobjects();
  bool save_level(string& filename);
  bool load_level(string& filename);
  
  SDL_Window* window;
  SDL_Surface* window_surface;

  string background_filename;

  int W, H, camera_x, camera_y, camera_speed;
  bool running, dragging, in_console;

  Uint32 lastUpdated;

  TTF_Font *font;

  //level editor specific stuff
  object_type current_type = start;

  void draw_hud();

  vector<Object*> to_clear;

  int wide_x, wide_y;
  bool setting_wide_obj, first_set_mouse_unrisen;
};

#endif //GAME_H
