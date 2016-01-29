#include <iostream>
#include <game.h>

using namespace std;

int main(int argc, char** argh)
{
  Game g(800, 600, "junaloikkuri");

  while(g.initialized()) {
    g.RunFrame();
  }
  
  return 0;
}
