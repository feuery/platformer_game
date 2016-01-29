#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_ttf.h>

class Game{
public:
  Game(int w, int h, const char* title);

  void RunFrame();
  bool initialized() const {
    return running;
  }

  ~Game();

private:
  SDL_Window* window;
  SDL_Surface* window_surface;

  int W, H;
  bool running;

  Uint32 lastUpdated;

  TTF_Font *font;
};

#endif //GAME_H
