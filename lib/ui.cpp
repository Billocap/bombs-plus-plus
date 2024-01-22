#include "ui.h"

// #region GridDrawer
/// @brief Creates a new grid drawer.
/// @param width This grids width.
/// @param height This grids height.
GridDrawer::GridDrawer(int width, int height)
{
  this->width = width;
  this->height = height;
}

/// @brief Draws a grid to the console.
void GridDrawer::draw()
{
  for (auto y = 0; y < this->height; y++)
  {
    for (auto x = 0; x < this->width; x++)
    {
      move(y, x * 2);

      printw("▒▒");
    }
  }

  printw("\n");
}
// #endregion GridDrawer

// #region Menus
// #region MenuOptionDrawer
/// @brief Creates a new menu option.
/// @param label Label for this option.
MenuOptionDrawer::MenuOptionDrawer(MenuDrawer *parent, std::string label)
{
  this->label = label;
  this->parent = parent;
}

/// @brief Marks this option as in focus.
void MenuOptionDrawer::focus()
{
  this->is_focused = true;
}

/// @brief Marks this option as out of focus.
void MenuOptionDrawer::blur()
{
  this->is_focused = false;
}

/// @brief Draws this option in the specified position.
/// @param y Y position to draw the option at.
/// @param x X position to draw the option at.
/// @return The updated Y position.
int MenuOptionDrawer::draw(int y, int x)
{
  auto label = this->label;

  if (this->is_focused)
  {
    label = "[" + label + "]";
  }

  mvprintw(y, x - label.length() / 2, label.c_str());

  return y + 1;
}
// #endregion MenuOptionDrawer

// #region MenuDrawer
/// @brief Adds a new option to this drawer.
/// @param label The new option's label.
void MenuDrawer::add_option(std::string label)
{
  this->options.push_back(new MenuOptionDrawer(this, label));
}

/// @brief Focus on the desired option.
/// @param id Id of the option to focus on.
void MenuDrawer::focus(int id)
{
  if (this->focused >= 0)
  {
    this->blur(this->focused);
  }

  this->focused = id;
  this->options[id]->focus();
}

/// @brief Makes the option out of focus.
/// @param id Id of the option to blur.
void MenuDrawer::blur(int id)
{
  this->focused = -1;
  this->options[id]->blur();
}

/// @brief Draws this menu.
void MenuDrawer::draw()
{
  int y = this->height / 4;
  int x = this->width / 2;

  init_pair(1, COLOR_YELLOW, COLOR_BLACK);

  auto banner_data = std::read_file("assets/banner");

  attron(COLOR_PAIR(1) | A_DIM);

  for (auto line : banner_data)
  {
    if (y >= this->height)
      break;

    mvprintw(y, x - line.length() / 2, line.c_str());

    y++;
  }

  init_pair(3, COLOR_WHITE, COLOR_BLACK);

  attroff(A_DIM);

  attron(COLOR_PAIR(3));

  y += 2;

  for (auto option : this->options)
  {
    if (y >= this->height)
      break;

    y = option->draw(y, x);
  }

  y += 2;

  if (y < this->height)
  {
    std::string line = "Created by Gabriel Quintino";

    init_pair(2, COLOR_BLUE, COLOR_BLACK);

    mvprintw(y, x - line.length() / 2, "Created by ");
    attron(COLOR_PAIR(2));
    printw("Gabriel Quintino");
    attron(COLOR_PAIR(3));
  }
}
// #endregion MenuDrawer
// #endregion Menus