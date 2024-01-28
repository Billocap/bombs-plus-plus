#include "game.h"

namespace std
{
  // #region Events

  GameRenderHandler::GameRenderHandler(Game *game)
  {
    this->game = game;
  }

  void GameRenderHandler::notify(RenderEvent *event)
  {
    if (this->game->screen == "game")
    {
      this->game->get_grid()->on_render->notify(event);
    }
    else
    {
      this->game->get_menu()->on_render->notify(event);
    }
  }

  GameKeyboardHandler::GameKeyboardHandler(Game *game)
  {
    this->game = game;
  }

  void GameKeyboardHandler::notify(KeyboardEvent *event)
  {
    if (this->game->screen == "game")
    {
      this->game->get_grid()->on_key_press->notify(event);
    }
    else
    {
      this->game->get_menu()->on_key_press->notify(event);
    }
  }

  GridStateHandler::GridStateHandler(Game *game)
  {
    this->game = game;
  }

  void GridStateHandler::notify(GridStateEvent *event)
  {
    this->game->finished = true;
    this->game->won = event->won;
  }

  // #endregion Events

  // #region Game

  Game::Game()
  {
    this->on_key_press = new GameKeyboardHandler(this);
    this->on_render = new GameRenderHandler(this);
    this->on_grid_state = new GridStateHandler(this);
  }

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

      this->grid->state->subscribe(this->on_grid_state);

      break;

    case D_MEDIUM:
      this->grid = new Grid(8, 8);

      this->grid->place_bombs(20);

      this->grid->state->subscribe(this->on_grid_state);

      break;

    case D_HARD:
      this->grid = new Grid(6, 6);

      this->grid->place_bombs(10);

      this->grid->state->subscribe(this->on_grid_state);

      break;
    }

    this->go_to("game");
  }

  /// @brief Returns the main grid.
  /// @return A pointer to the main grid.
  Grid *Game::get_grid()
  {
    return this->grid;
  }

  /// @brief Adds a new menu to the list of available menus.
  /// @param name Unique id for this menu.
  /// @param menu Pointer to the menu object.
  void Game::add_menu(string name, Menu *menu)
  {
    this->menus[name] = menu;

    if (this->screen == "")
    {
      this->screen = name;
    }
  }

  /// @brief Changes the current game screen.
  /// @param name Name of the screen to load.
  void Game::go_to(string name)
  {
    this->screen = name;
  }

  Menu *Game::get_menu()
  {
    return this->menus[this->screen];
  }

  // #endregion Game
}
