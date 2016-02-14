#include <iostream>
#include <allegro5/allegro.h>
#include "gameboard.h"

using namespace std;
using namespace gamewindow;
using namespace game_exceptions;

int main()
{
  cout << "starting a game window..." << endl;
  Gamewindow breakout(850,500,60);

  try
  {
      breakout.inut_allegro();
      breakout.inut_game_elems();
  }
  catch(InutException &e)
  {
      e.printError();
  }

  breakout.game_loop();

  return 0;
}
