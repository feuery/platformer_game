#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>
#include <vector>
#include <object_type.h>

using namespace std;

class Object{
public:

  // Object(int r, int g, int b, int W, int H, object_type t);
  Object(const char* path, object_type t);
  Object(SDL_Surface* img, object_type t);
  Object(object_type t);

  static vector<Object*> objects;
  static bool collides(int x_1, int y_1, int width_1, int height_1);
  static int amount_of_otype(object_type t);
  
  int X, Y;
  bool visible;

  virtual void draw(SDL_Surface* window, int camera_x, int camera_y);

  void RemoveFromQueue();
  void AddToQueue();

  int getW();
  int getH();

  object_type type;
  
  virtual ~Object();
private:
  
  SDL_Surface* img;
  bool should_free_img;

  void init_object(int r, int g, int b, int W, int H);
};

#endif //OBJECT_H
