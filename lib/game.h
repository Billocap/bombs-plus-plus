#ifndef GAME_H
#define GAME_H

#include <map>
#include <string>
#include <ncursesw/ncurses.h>

#include "events.h"
#include "grid.h"
#include "menu.h"

namespace std
{
  class Game;

  enum Difficulty
  {
    D_EASY,
    D_MEDIUM,
    D_HARD,
    D_CUSTOM
  };

  // #region Events

  class GameRenderHandler : public IEventHandler<RenderEvent>
  {
  public:
    GameRenderHandler(Game *game);

    void notify(RenderEvent *event);

  private:
    Game *game;
  };

  class GameKeyboardHandler : public IEventHandler<KeyboardEvent>
  {
  public:
    GameKeyboardHandler(Game *game);

    void notify(KeyboardEvent *event);

  private:
    Game *game;
  };

  class GridStateHandler : public IEventHandler<GridStateEvent>
  {
  public:
    GridStateHandler(Game *game);

    void notify(GridStateEvent *event);

  private:
    Game *game;
  };

  // #endregion Events

  class Game
  {
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

  private:
    /// @brief Defines if the game is running or not.
    bool running = true;
    /// @brief The main grid this game happens on.
    Grid *grid;
    /// @brief If the game is running but paused.
    bool paused = false;
    /// @brief Map of available menus.
    map<string, Menu *> menus;
  };
}

void render_state(std::string message, int x, int y);

#endif
