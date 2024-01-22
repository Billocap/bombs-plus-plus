#include <ncurses.h>
#include <string>
#include <iostream>

#include "lib/assert.h"
#include "lib/grid.h"
#include "lib/ui.h"
#include "lib/game.h"
#include "lib/io.h"
#include "lib/menuopts.h"
#include "lib/menu.h"

using namespace std;

int main()
{
  Game main_game;

  main_game.start();

  GridDrawer drawer;

  WINDOW *main_window = initscr();

  start_color();

  int w, h;

  curs_set(0);

  int curr_menu = 0;

  Menu menu;

  menu.add_option("Continue", new EmptyOption());
  menu.add_option("New game", new GoToOption(&curr_menu, 1));
  menu.add_option("Exit", new ExitOption(&main_game));

  Menu diff_menu;

  diff_menu.add_option("Easy", new NewGameOption(&main_game, EASY, &curr_menu, 2));
  diff_menu.add_option("Medium", new NewGameOption(&main_game, MEDIUM, &curr_menu, 2));
  diff_menu.add_option("Hard", new NewGameOption(&main_game, HARD, &curr_menu, 2));
  diff_menu.add_option("Back", new GoToOption(&curr_menu, 0));

  while (main_game.is_running())
  {
    clear();

    getmaxyx(main_window, h, w);

    menu.drawer->width = w;
    menu.drawer->height = h;

    diff_menu.drawer->width = w;
    diff_menu.drawer->height = h;

    switch (curr_menu)
    {
    case 0:
      menu.drawer->draw();
      break;

    case 1:
      diff_menu.drawer->draw();
      break;

    case 2:
      drawer.draw(main_game.get_grid());
      break;
    }

    refresh();

    auto c = getch();

    switch (curr_menu)
    {
    case 0:
      menu.handle_input(c);
      break;

    case 1:
      diff_menu.handle_input(c);
      break;
    }
  }

  endwin();

  curs_set(1);

  return 0;
}
