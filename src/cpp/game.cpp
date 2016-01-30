#include <game.h>
#include <object.h>
#include <object_type.h>

#include <iostream>
#include <string>

using namespace std;

Game::Game(int w, int h, const char* title): W(w), H(h),  dragging(false), lastUpdated(0), camera_x(0), camera_y(0), running(false), camera_speed(10)
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
      dragging = false;
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

bool operator==(pair<int, int> a, pair<int, int> b) {
  return a.first == b.first && a.second == b.second;
}
  

template<typename T>
bool contains(vector<T> vec, T val) {
  for(auto i = vec.begin(); i != vec.end(); i++) {
    if(*i == val) return true;
  }
  return false;
}



void Game::RunFrame() {
  //If eventloop says we're to quit, don't bother drawing another frame
  if(!eventloop()) return;

  if(dragging) {
    int x, y;
    if(SDL_GetMouseState(&x, &y)) {

      int r = 0, g = 0, b = 0;
      int w = 80, h = 100;
      printf("Amount of objects %d\n", Object::objects.size());
      printf("Amount of objects of type %s: %d\n", otype_to_string(current_type), Object::amount_of_otype(current_type));

      if(Object::amount_of_otype(current_type) < amount_of_otypes_allowed(current_type) &&
	 !Object::collides(x, y, w, h)) {
	otype_to_rgb(current_type, r, g, b);
	Object* obj = new Object(r, g, b, w, h, current_type);
	obj->X = x;
	obj->Y = y;
	to_clear.push_back(obj);
      }
      printf("Amount of objects %d\n", Object::objects.size());
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
  
  SDL_FreeSurface(text);
  SDL_FreeSurface(camera_text);
  SDL_FreeSurface(increase_text);
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
