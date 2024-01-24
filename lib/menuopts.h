#ifndef MENU_OPTIONS_H
#define MENU_OPTIONS_H

#include <string>

#include "menu.h"
#include "game.h"

namespace std
{
  /// @brief Represents a menu option that does nothing.
  class EmptyOption : public IMenuOption
  {
  public:
    void execute();
  };

  /// @brief Represents a menu option that exits the game.
  class ExitOption : public IMenuOption
  {
  public:
    ExitOption(Game *game);

    void execute();

  private:
    Game *game;
  };

  /// @brief Represents a menu option that changes the current screen.
  class GoToOption : public IMenuOption
  {
  public:
    GoToOption(Game *game, string name);

    void execute();

  private:
    Game *game;
    string name;
  };

  /// @brief Represents a menu options that starts a new game.
  class NewGameOption : public IMenuOption
  {
  public:
    NewGameOption(Game *game, Difficulty diff);

    void execute();

  private:
    Game *game;
    Difficulty diff;
  };
};

#endif
