#include <iostream>
#include <game.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

void real_sleep(int ms) {
#ifdef _WIN32
  Sleep(ms);
#else
  usleep(ms*1000);  /* sleep for 100 milliSeconds */
#endif
}

int main(int argc, char** argh)
{
  Game g(1280, 950, "junaloikkuri");

  while(g.initialized()) {
    g.RunFrame();
    real_sleep(40);
  }
  
  return 0;
}
