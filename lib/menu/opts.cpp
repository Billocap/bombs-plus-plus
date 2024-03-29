#include <menu/opts.h>

void EmptyOption::execute() {}

// #region ExitOption

ExitOption::ExitOption(Game *game) : IMenuAction()
{
  this->game = game;
}

void ExitOption::execute()
{
  this->game->stop();
}

// #endregion ExitOption

// #region ContinueOption

ContinueOption::ContinueOption(Game *game)
{
  this->game = game;
}

void ContinueOption::execute()
{
  this->game->load_data();
}

// #endregion ContinueOption

// #region GoToOption

GoToOption::GoToOption(Game *game, std::string name) : IMenuAction()
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

NewGameOption::NewGameOption(Game *game, Difficulty diff) : IMenuAction()
{
  this->game = game;
  this->diff = diff;
}

void NewGameOption::execute()
{
  this->game->new_game(this->diff);
}

// #endregion NewGameOption
