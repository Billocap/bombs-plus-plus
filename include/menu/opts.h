#ifndef MENU_ACTIONS_H
#define MENU_ACTIONS_H

#include <string>

#include <game/game.h>

#include "menu.h"

namespace std
{
  /// @brief Represents a menu option that does nothing.
  class EmptyOption : public IMenuAction
  {
  public:
    void execute();
  };

  /// @brief Represents a menu option that loads previous saves.
  class ContinueOption : public IMenuAction
  {
  public:
    ContinueOption(Game *game);

    void execute();

  private:
    Game *game;
  };

  /// @brief Represents a menu option that exits the game.
  class ExitOption : public IMenuAction
  {
  public:
    ExitOption(Game *game);

    void execute();

  private:
    Game *game;
  };

  /// @brief Represents a menu option that changes the current screen.
  class GoToOption : public IMenuAction
  {
  public:
    GoToOption(Game *game, string name);

    void execute();

  private:
    Game *game;
    string name;
  };

  /// @brief Represents a menu options that starts a new game.
  class NewGameOption : public IMenuAction
  {
  public:
    NewGameOption(Game *game, Difficulty diff);

    void execute();

  private:
    Game *game;
    Difficulty diff;
  };
}

#endif
