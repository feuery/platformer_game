#include <object.h>
#include <SDL_image.h>

vector<Object*> Object::objects;

Object::Object(int r, int g, int b, int W, int H): X(0), Y(0), visible(true), should_free_img(true)
{
  Uint32 rmask, gmask, bmask, amask;

  /* SDL interprets each pixel as a 32-bit number, so our masks must depend
     on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
#else
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0xff000000;
#endif

  img = SDL_CreateRGBSurface(0, W, H, 32, rmask, gmask, bmask, amask);
  SDL_FillRect(img, NULL, SDL_MapRGB(img->format, r, g, b));

  objects.push_back(this);
}

Object::Object(const char* path): img(IMG_Load(path)), should_free_img(true), X(0), Y(0), visible(true)
{
  objects.push_back(this);
}

Object::Object(SDL_Surface* img): img(img), should_free_img(false), X(0), Y(0), visible(true)
{
  objects.push_back(this);
}

Object::~Object()
{
  for(auto it = objects.begin(); it != objects.end(); it++) {
    if(*it == this) {
      objects.erase(it);
      break;
    }
  }      
  
  if(!should_free_img) return;

  SDL_FreeSurface(img);
}
  
void Object::draw(SDL_Surface* window, int camera_x, int camera_y)
{
  if(!visible) return;
  int x = X - camera_x,
    y = Y - camera_y;

  SDL_Rect dst = {x, y, 0, 0};
  SDL_BlitSurface(img, NULL, window, &dst);
}

int Object::getW() {
  printf("Object::getW() -> %d\n", img->w);
  return img->w;
}

int Object::getH() {
  printf("Object::getH() -> %d\n", img->h);
  return img->h;
}

bool Object::collides(int x_1, int y_1, int width_1, int height_1)
{
  
  for(auto it = objects.begin(); it != objects.end(); it++) {
    int x_2 = (*it)->X, y_2 = (*it)->Y, width_2 = (*it)->getW(), height_2 = (*it)->getH();
    //could probs. be prittified, but I'm on a time limit here
    if(!(x_1 > x_2+width_2 || x_1+width_1 < x_2 || y_1 > y_2+height_2 || y_1+height_1 < y_2))
      return true;
  }

  return false;
}
