#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>
#include <vector>

using namespace std;

class Object{
public:

  Object(int r, int g, int b, int W, int H);
  Object(const char* path);
  Object(SDL_Surface* img);

  static vector<Object*> objects;

  static bool collides(int x, int y);
  
  int X, Y;
  bool visible;

  virtual void draw(SDL_Surface* window, int camera_x, int camera_y);

  int getW();
  int getH();
  
  ~Object();
private:
  
  SDL_Surface* img;
  bool should_free_img;
};

#endif //OBJECT_H
