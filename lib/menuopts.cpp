#include <menu/opts.h>

namespace std
{
  void EmptyOption::execute() {}

  // #region ExitOption

  ExitOption::ExitOption(Game *game) : IMenuOption()
  {
    this->game = game;
  }

  void ExitOption::execute()
  {
    this->game->stop();
  }

  // #endregion ExitOption

  // #region GoToOption

  GoToOption::GoToOption(Game *game, string name) : IMenuOption()
  {
    this->game = game;
    this->name = name;
  }

  void GoToOption::execute()
  {
    this->game->go_to(this->name);
  }

  // #endregion GoToOption

  // #region NewGameOption

  NewGameOption::NewGameOption(Game *game, Difficulty diff) : IMenuOption()
  {
    this->game = game;
    this->diff = diff;
  }

  void NewGameOption::execute()
  {
    this->game->new_game(this->diff);
  }

  // #endregion NewGameOption
}
