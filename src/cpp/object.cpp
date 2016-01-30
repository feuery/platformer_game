#include <object.h>
#include <SDL_image.h>

Object::Object(const char* path): should_free_img(true), img(IMG_Load(path)), X(0), Y(0)
{
  objects.push_back(this);
}

Object::Object(SDL_Surface* img): should_free_img(false), img(img), X(0), Y(0)
{
  objects.push_back(this);
}

Object::~Object()
{
  for(auto it = objects.begin(); it != objects.end(); it++) {
    if(*it == this) {
      objects.erase(it);
    }
  }      
  
  if(!should_free_img) return;

  SDL_FreeSurface(img);
}
  
void Object::draw(SDL_Surface* window, int camera_x, int camera_y)
{
  int x = X - camera_x,
    y = Y - camera_y;

  SDL_Rect dst = {x, y, 0, 0};
  SDL_BlitSurface(img, NULL, window, &dst);
}
