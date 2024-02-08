#include <game/events.h>
#include <game/game.h>
#include <game/render.h>

// #region Events

GameRenderHandler::GameRenderHandler(Game *game)
{
  this->game = game;
}

void GameRenderHandler::notify(RenderEvent *event)
{
  if (this->game->screen == "game")
  {
    if (this->game->finished)
    {
      std::string message = this->game->won ? "You Won" : "You Lost";

      int x = event->x - (message.size() / 2);
      int y = event->y - 1;

      render_state(message, x, y);
    }

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
    if (this->game->finished)
    {
      delete this->game->get_grid();

      this->game->go_to("main");
    }
    else
    {
      this->game->save_data();

      this->game->get_grid()->on_key_press->notify(event);
    }
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
  delete_save("save");

  this->game->pause();
  this->game->finished = true;
  this->game->won = event->won;

  auto main_menu = this->game->get_menu("main");

  if (main_menu->options[0]->label == "Continue")
    main_menu->remove_option(0);
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
  this->resume();

  this->finished = false;
  this->won = false;

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

  this->save_data();

  this->grid->state->subscribe(this->on_grid_state);
  this->go_to("game");
}

/// @brief Creates a new game from a previous save file.
void Game::load_data()
{
  this->resume();

  this->finished = false;
  this->won = false;

  delete this->grid;

  this->grid = new Grid(8, 8);

  auto data = read_save("save");

  this->grid->from_save(data);

  this->grid->state->subscribe(this->on_grid_state);
  this->go_to("game");
}

/// @brief Saves the game by overwriting previous save.
void Game::save_data()
{
  auto data = this->grid->to_save();

  if (data.length() > 0)
    write_save("save", data);
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
void Game::add_menu(std::string name, Menu *menu)
{
  this->menus[name] = menu;

  if (this->screen == "")
  {
    this->screen = name;
  }
}

/// @brief Changes the current game screen.
/// @param name Name of the screen to load.
void Game::go_to(std::string name)
{
  this->screen = name;
}

Menu *Game::get_menu()
{
  return this->menus[this->screen];
}

Menu *Game::get_menu(std::string name)
{
  return this->menus[name];
}

// #endregion Game

void render_state(std::string message, int x, int y)
{
  mvprintw(y, x, message.c_str());
}
