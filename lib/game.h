#ifndef GAME_H
#define GAME_H

#include <map>
#include <string>

#include "io.h"
#include "grid.h"

namespace std
{
  enum Difficulty
  {
    D_EASY,
    D_MEDIUM,
    D_HARD,
    D_CUSTOM
  };

  class ScreenManager
  {
  };

  class Game : public IInputHandler
  {
  public:
    bool is_running();
    bool is_paused();
    void start();
    void pause();
    void resume();
    void stop();
    void new_game(Difficulty diff);
    Grid *get_grid();
    void handle_input(int key);

  private:
    /// @brief Defines if the game is running or not.
    bool running = true;
    /// @brief The main grid this game happens on.
    Grid *grid;
    /// @brief If the game is running but paused.
    bool paused = false;
  };
}

#endif
