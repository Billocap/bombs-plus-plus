#ifndef GAME_H
#define GAME_H

#include <map>
#include <string>

#include <grid/grid.h>
#include <menu/menu.h>

#include "events.h"

namespace std
{
  enum Difficulty
  {
    D_EASY,
    D_MEDIUM,
    D_HARD,
    D_CUSTOM
  };

  class Game
  {
  private:
    /// @brief Defines if the game is running or not.
    bool running = true;
    /// @brief The main grid this game happens on.
    Grid *grid;
    /// @brief If the game is running but paused.
    bool paused = false;
    /// @brief Map of available menus.
    map<string, Menu *> menus;

  public:
    /// @brief Tells if the game has finished but not stoped.
    bool finished = false;
    /// @brief Tells if the game was won.
    bool won = false;
    /// @brief Current screen being managed.
    string screen;

    GameKeyboardHandler *on_key_press;
    GameRenderHandler *on_render;
    GridStateHandler *on_grid_state;

    Game();

    bool is_running();
    bool is_paused();
    void start();
    void pause();
    void resume();
    void stop();
    void new_game(Difficulty diff);
    Grid *get_grid();
    void add_menu(string name, Menu *menu);
    void go_to(string name);
    Menu *get_menu();
  };
}

#endif
