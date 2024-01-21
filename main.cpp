#include <iostream>
#include <ncurses.h>

#include "lib/assert.h"
#include "lib/grid.h"
#include "lib/gridui.h"

using namespace std;

int main()
{
  Grid grid(4, 4);

  grid.place_bombs(10);

  GridDrawer drawer;

  WINDOW *main_window = initscr();

  int w, h;

  getmaxyx(main_window, h, w);

  cout << w << "x" << h << endl;

  clear();

  drawer.draw(&grid);

  refresh();

  return 0;
}
