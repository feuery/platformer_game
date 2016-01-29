#include <game.h>
#include <iostream>

using namespace std;

Game::Game(int w, int h, const char* title): W(w), H(h), lastUpdated(0)
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

void Game::RunFrame() {
  SDL_Event e;
  while(SDL_PollEvent(&e)) {
    switch(e.type) {
    case SDL_QUIT:
      cout<<"Not running!"<<endl;
      running = false;
      break;
    case SDL_MOUSEBUTTONDOWN:
      cout<<"Implement dragging here"<<endl;
      break;
    case SDL_MOUSEBUTTONUP:
      cout<<"Implement drag-stop here"<<endl;
      break;
    }
 } 
}

Game::~Game() {
}
