#define _XOPEN_SOURCE_EXTENDED

#include <ncursesw/ncurses.h>
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

#include <events/dispatcher.h>
#include <events/events.h>
#include <game/game.h>
#include <grid/grid.h>
#include <menu/menu.h>
#include <menu/opts.h>
#include <ui/ui.h>
#include <io.h>

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

  TextBanner title_banner("assets/banner");

  Menu menu(&title_banner);

  if (filesystem::exists("save"))
    menu.add_option("Continue", new ContinueOption(&main_game));

  menu.add_option("New game", new GoToOption(&main_game, "diff"));
  menu.add_option("Exit", new ExitOption(&main_game));

  Menu diff_menu(&title_banner);

  diff_menu.add_option("Easy", new NewGameOption(&main_game, D_EASY));
  diff_menu.add_option("Medium", new NewGameOption(&main_game, D_MEDIUM));
  diff_menu.add_option("Hard", new NewGameOption(&main_game, D_HARD));
  diff_menu.add_option("Back", new GoToOption(&main_game, "main"));

  main_game.add_menu("main", &menu);
  main_game.add_menu("diff", &diff_menu);

  EventDispatcher<KeyboardEvent> keyboard;

  keyboard.subscribe(main_game.on_key_press);

  EventDispatcher<RenderEvent> renderer;

  renderer.subscribe(main_game.on_render);

  while (main_game.is_running())
  {
    clear();

    getmaxyx(main_window, h, w);

    renderer.notify(new RenderEvent(w, h, w / 2, h / 4));

    refresh();

    attron(A_INVIS);

    int c = getch();

    keyboard.notify(new KeyboardEvent(c));

    attroff(A_INVIS);
  }

  attroff(A_INVIS);

  curs_set(1);

  endwin();

  return 0;
}
