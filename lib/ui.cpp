#include "ui.h"

// #region GridDrawer
/// @brief Draws a grid to the console.
/// @param grid Pointer to the grid to be drawn.
void GridDrawer::draw(std::Grid *grid)
{
  for (auto y = 0; y < grid->height; y++)
  {
    for (auto x = 0; x < grid->width; x++)
    {
      move(y, x * 2);

      printw("[]");
    }
  }

  printw("\n");
}
// #endregion GridDrawer

// #region Menus
// #region MenuOptionDrawer
/// @brief Creates a new menu option.
/// @param label Label for this option.
MenuOptionDrawer::MenuOptionDrawer(std::string label)
{
  this->label = label;
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

/// @brief Returns this option's label in the correct format.
/// @return This option's label.
std::string MenuOptionDrawer::get_draw_label()
{
  auto label = this->label;

  if (this->is_focused)
  {
    label = "[" + label + "]";
  }

  return label;
}
// #endregion MenuOptionDrawer

// #region MenuDrawer
/// @brief Adds a new option to this drawer.
/// @param label The new option's label.
void MenuDrawer::add_option(std::string label)
{
  auto op = new MenuOptionDrawer(label);

  this->options.push_back(op);
}

/// @brief Focus on the desired option.
/// @param id Id of the option to focus on.
void MenuDrawer::focus(int id)
{
  if (this->focused >= 0)
  {
    this->blur(this->focused);

    this->focused = id;
  }

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
  int y = 0;

  auto banner_data = std::read_file("assets/banner");

  for (auto line : banner_data)
  {
    move(y, 0);

    printw(line.c_str());

    y++;
  }

  y += 2;

  for (auto option : this->options)
  {
    auto line = option->get_draw_label();

    move(y, 0);
    printw(line.c_str());

    y++;
  }

  y += 2;

  move(y, 0);
  printw("Created by Gabriel Quintino 2023");
}
// #endregion MenuDrawer
// #endregion Menus