#ifndef GAME_H
#define GAME_H

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

  class Game
  {
  public:
    bool is_running();
    void start();
    void stop();
    void new_game(Difficulty diff);
    Grid *get_grid();

  private:
    /// @brief Defines if the game is running or not.
    bool running = true;
    /// @brief The main grid this game happens on.
    Grid *grid;
  };
}

#endif
