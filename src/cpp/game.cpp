#include <game.h>
#include <iostream>

using namespace std;

Game::Game(int w, int h, const char* title): W(w), H(h),  dragging(false), lastUpdated(0)
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
      printf("Loading font failed");
      return;
    }
  
  atexit(SDL_Quit);
  atexit(TTF_Quit);
  running = true;

  cout<<"Inited successfully"<<endl;
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
  if(!eventloop()) return;

  if(dragging) {
    int x, y;
    if(SDL_GetMouseState(&x, &y)) {
      pair<int, int> coord(x, y);

      if(!contains<pair<int, int>>(where_dragged, coord)) {
	where_dragged.push_back(coord);
	printf("Pushed coordinates [%d, %d] to container\n", x, y);
      }
    }
  }
}

Game::~Game() {
}
