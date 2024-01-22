#include "menuopts.h"

namespace std
{
  void EmptyOption::execute() {}

  // #region ExitOption
  ExitOption::ExitOption(Game *game) : MenuOption()
  {
    this->game = game;
  }

  void ExitOption::execute()
  {
    this->game->stop();
  }
  // #endregion ExitOption

  // #region GoToOption
  GoToOption::GoToOption(int *state, int id) : MenuOption()
  {
    this->state = state;
    this->id = id;
  }

  void GoToOption::execute()
  {
    *(this->state) = this->id;
  }
  // #endregion GoToOption

  // #region NewGameOption
  NewGameOption::NewGameOption(Game *game, Difficulty diff, int *state, int id) : MenuOption()
  {
    this->game = game;
    this->diff = diff;
    this->state = state;
    this->id = id;
  }

  void NewGameOption::execute()
  {
    *(this->state) = this->id;
    this->game->new_game(this->diff);
  }

  // #endregion NewGameOption
}
