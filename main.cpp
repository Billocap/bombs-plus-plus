#include <ncurses.h>
#include <string>

#include "lib/assert.h"
#include "lib/grid.h"
#include "lib/ui.h"
#include "lib/game.h"
#include "lib/io.h"

using namespace std;

int main()
{
  Game main_game;

  main_game.start();

  Grid grid(4, 4);

  grid.place_bombs(10);

  GridDrawer drawer;

  WINDOW *main_window = initscr();

  int w, h;

  curs_set(0);

  MenuDrawer menu;

  menu.add_option("Continue");
  menu.add_option("New game");
  menu.add_option("Exit");

  menu.focus(0);

  while (main_game.is_running())
  {
    clear();

    menu.draw();

    refresh();

    auto c = getch();

    if (c != 0)
    {
      main_game.stop();
    }
  }

  endwin();

  return 0;
}
