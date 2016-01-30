#include <game.h>
#include <object.h>
#include <object_type.h>

#include <iostream>
#include <string>

using namespace std;

int etsi_lahin_tasan_jaettava(int n, int divisor)
{
  int nn = n / divisor;
  return nn * divisor;
}

Game::Game(int w, int h, const char* title): W(w), H(h),  dragging(false), lastUpdated(0), camera_x(0), camera_y(0), running(false), camera_speed(10), wide_x(0), wide_y(0), setting_wide_obj(false), first_set_mouse_unrisen(false)
{
  cout<<"Initing everything"<<endl;
  if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
    {
      fprintf(stderr, "Virhe %s\n", SDL_GetError());
      return;
    }

  window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
  if (window == nullptr)
    {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
      return;
    }

  if(TTF_Init() == -1)
    {
      printf("TTF_Init: %s\n", TTF_GetError());
      return;
    }
  
  this->window_surface = SDL_GetWindowSurface(this->window);
  font = TTF_OpenFont("./DejaVuSans-Bold.ttf", 30);

  if(!font)
    {
      printf("Loading font failed\n");
      return;
    }

  atexit(SDL_Quit);
  atexit(TTF_Quit);
  running = true;

  cout<<"Inited successfully"<<endl;
}

void Game::do_kbd_up(SDL_Event& e) {
  switch(e.key.keysym.sym) {
  case SDLK_LEFT:
    current_type--;
    break;
  case SDLK_RIGHT:
    current_type++;
    break;
  }
}

void Game::do_kbd_down(SDL_Event& e) {
  switch(e.key.keysym.sym) {
  case SDLK_a:
    camera_x-= camera_speed;
    break;
  case SDLK_s:
    camera_y+= camera_speed;
    break;
  case SDLK_d:
    camera_x+= camera_speed;
    break;
  case SDLK_w:
    camera_y-= camera_speed;
    break;

  case SDLK_e:
    camera_speed += 5;
    break;
  case SDLK_f:
    camera_speed -= 5;
    break;    
  }
}

bool Game::eventloop() {
  bool notquit = true;
  SDL_Event e;
  
  while(SDL_PollEvent(&e)) {
    switch(e.type) {
    case SDL_QUIT:
      cout<<"Not running!"<<endl;
      notquit = running = false;
      break;
    case SDL_MOUSEBUTTONDOWN:
      cout<<"Dragging"<<endl;
      dragging = true;
      break;
    case SDL_MOUSEBUTTONUP:
      cout<<"Not dragging"<<endl;
      first_set_mouse_unrisen = dragging = false;
      break;

    case SDL_KEYUP:
      do_kbd_up(e);
      break;
    case SDL_KEYDOWN:
      do_kbd_down(e);
      break;
    }
  }

  return notquit;
}

void Game::place_narrow_object(int x, int y) {
  Object* obj = new Object(current_type);
  obj->X = x;
  obj->Y = y;

  if(Object::amount_of_otype(current_type) < amount_of_otypes_allowed(current_type) &&
     !Object::collides(obj->X, obj->Y, obj->getW(), obj->getH())) {
    to_clear.push_back(obj);
  }
  else delete obj;
}

void Game::place_wide_object(int x, int y) {
  first_set_mouse_unrisen = true;
  
  if(!setting_wide_obj) {
    wide_x = x;
    wide_y = y;
    setting_wide_obj = true;
    return;
  }

  Object o(current_type);
  o.visible = false;
  
  int W = o.getW();
  
  int higher_x = etsi_lahin_tasan_jaettava(max(x, wide_x), W);
  int lower_x = etsi_lahin_tasan_jaettava(min(x, wide_x), W);

  for(int in_between_x = lower_x; in_between_x <= higher_x; in_between_x += W) {
    Object* in_between = new Object(current_type);
    in_between->X = in_between_x;
    in_between->Y = wide_y;
    
    to_clear.push_back(in_between);
  }

  setting_wide_obj = false;
}

void Game::RunFrame() {
  //If eventloop says we're to quit, don't bother drawing another frame
  if(!eventloop()) return;

  if(dragging && !first_set_mouse_unrisen) {
    int x, y;
    if(SDL_GetMouseState(&x, &y)) {

      if (otype_is_wide(current_type)) place_wide_object(x, y);
      else place_narrow_object(x, y);
 
    }
  }

  drawobjects();
  draw_hud();

  SDL_UpdateWindowSurface(window);
  SDL_FillRect(window_surface, NULL, SDL_MapRGB(window_surface->format, 0, 0, 0));
}

void Game::draw_hud() {
  SDL_Surface* text = to_surface((string("Selected type: ")+otype_to_string(current_type)).c_str());
  SDL_Rect text_location = {10, 10, 0, 0};
  SDL_BlitSurface(text, NULL, window_surface, &text_location);

  SDL_Surface* camera_text = to_surface("Use WASD to move camera");
  int new_y = 15 + text->h;
  text_location = {10, new_y, 0, 0};
  SDL_BlitSurface(camera_text, NULL, window_surface, &text_location);

  string increase_str_text = "Use F and E to incr and decr camera speed (";
  increase_str_text += std::to_string(camera_speed) + ")";
  
  SDL_Surface* increase_text = to_surface(increase_str_text.c_str());
  new_y += camera_text->h + 5;
  text_location = {10, new_y, 0, 0};
  SDL_BlitSurface(increase_text, NULL, window_surface, &text_location);

  SDL_Surface* setting_wide_surface = to_surface(setting_wide_obj? "Setting wide objects": "Not setting wide objects");
  new_y += increase_text->h + 5;
  text_location = {10, new_y, 0, 0};
  SDL_BlitSurface(setting_wide_surface, NULL, window_surface, &text_location);
  
  SDL_FreeSurface(text);
  SDL_FreeSurface(camera_text);
  SDL_FreeSurface(increase_text);
  SDL_FreeSurface(setting_wide_surface);
}

void Game::drawobjects(){
  // printf("Drawing %d objects\n", Object::objects.size());

  for(auto obj_it = Object::objects.begin(); obj_it != Object::objects.end(); obj_it++) {
  
    (*obj_it)->draw(window_surface, camera_x, camera_y);
  }

  // printf("Drawing finished\n");
}


SDL_Surface* Game::to_surface(const char* str) {
  return TTF_RenderUTF8_Solid(font, str, {0xFF, 0xFF, 0xFF});
}

Game::~Game() {
  for(auto it = to_clear.begin(); it != to_clear.end(); it++)
    delete *it;
}
