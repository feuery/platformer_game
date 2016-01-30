#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>
#include <vector>

using namespace std;

class Object{
public:

  Object(const char* path);
  Object(SDL_Surface* img);

  static vector<Object*> objects;
  int X, Y;

  virtual void draw(SDL_Surface* window, int camera_x, int camera_y);
  
  ~Object();
private:
  
  SDL_Surface* img;
  bool should_free_img;
};

#endif //OBJECT_H
