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

  /// @brief Used to check if the game is running but paused.
  /// @return The pause state of the game.
  bool Game::is_paused()
  {
    return this->paused;
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

  /// @brief Pauses the game.
  void Game::pause()
  {
    this->paused = true;
  }

  /// @brief Resumes the game.
  void Game::resume()
  {
    this->paused = false;
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

  /// @brief Handles keyboard input.
  /// @param key ASCII code for the key pressed.
  void Game::handle_input(int key)
  {
    if (this->paused)
    {
      switch (key)
      {
      case IO_KEY_MENU:
        this->resume();
        break;
      }
    }
    else
    {
      switch (key)
      {
      case IO_KEY_MENU:
        this->pause();
        break;

      default:
        this->grid->handle_input(key);
        break;
      }
    }
  }

  // #endregion Game
}
