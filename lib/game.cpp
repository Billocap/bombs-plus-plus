#include "game.h"

namespace std
{
  // #region Game
  /// @brief Used to check if the game is running.
  /// @return The state of the game.
  bool Game::is_running()
  {
    return this->running;
  }

  /// @brief Starts the execution of the game.
  void Game::start()
  {
    this->running = true;
  }

  /// @brief Stops the execution of the game.
  void Game::stop()
  {
    this->running = false;
  }

  /// @brief Start a new game.
  /// @param diff The difficulty of the new game.
  void Game::new_game(Difficulty diff)
  {
    switch (diff)
    {
    case D_EASY:
      this->grid = new Grid(8, 8);

      this->grid->place_bombs(10);

      break;

    case D_MEDIUM:
      this->grid = new Grid(8, 8);

      this->grid->place_bombs(20);

      break;

    case D_HARD:
      this->grid = new Grid(6, 6);

      this->grid->place_bombs(10);

      break;
    }
  }

  /// @brief Returns the main grid.
  /// @return A pointer to the main grid.
  Grid *Game::get_grid()
  {
    return this->grid;
  }
  // #endregion Game
}
