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
  // #endregion Game
}
