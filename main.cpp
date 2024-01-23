#define _XOPEN_SOURCE_EXTENDED

#include <ncursesw/ncurses.h>
#include <string>
#include <iostream>

#include "lib/grid.h"
#include "lib/ui.h"
#include "lib/game.h"
#include "lib/io.h"
#include "lib/menuopts.h"
#include "lib/menu.h"

using namespace std;

int main()
{
  setlocale(LC_ALL, "en_US.UTF-8");

  Game main_game;

  main_game.start();

  WINDOW *main_window = initscr();

  start_color();

  int w, h;

  curs_set(0);

  int curr_menu = 0;

  TextBanner title_banner("assets/banner");

  Menu menu;

  // menu.add_option("Continue", new EmptyOption());
  menu.add_option("New game", new GoToOption(&curr_menu, 1));
  menu.add_option("Exit", new ExitOption(&main_game));

  menu.drawer->set_banner(&title_banner);
  menu.drawer->focus(0);

  Menu diff_menu;

  diff_menu.add_option("Easy", new NewGameOption(&main_game, D_EASY, &curr_menu, 2));
  diff_menu.add_option("Medium", new NewGameOption(&main_game, D_MEDIUM, &curr_menu, 2));
  diff_menu.add_option("Hard", new NewGameOption(&main_game, D_HARD, &curr_menu, 2));
  diff_menu.add_option("Back", new GoToOption(&curr_menu, 0));

  diff_menu.drawer->set_banner(&title_banner);
  diff_menu.drawer->focus(0);

  while (main_game.is_running())
  {
    clear();

    getmaxyx(main_window, h, w);

    switch (curr_menu)
    {
    case 0:
      menu.drawer->resize_clip_box(h, w);
      menu.drawer->draw(h / 4, w / 2);
      break;

    case 1:
      diff_menu.drawer->resize_clip_box(h, w);
      diff_menu.drawer->draw(h / 4, w / 2);
      break;

    case 2:
      main_game.get_grid()->drawer->draw(h / 4, w / 2);
      break;
    }

    refresh();

    attron(A_INVIS);

    unsigned int c = getch();

    switch (curr_menu)
    {
    case 0:
      menu.handle_input(c);
      break;

    case 1:
      diff_menu.handle_input(c);
      break;

    case 2:
      main_game.handle_input(c);
      break;
    }

    attroff(A_INVIS);
  }

  attroff(A_INVIS);

  curs_set(1);

  endwin();

  return 0;
}
