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
  if (this->is_focused)
  {
    return "[" + this->label + "]";
  }

  return this->label;
}
// #endregion MenuOptionDrawer

// #region MenuDrawer
/// @brief Adds a new option to this drawer.
/// @param label The new option's label.
void MenuDrawer::add_option(std::string label)
{
  this->options.push_back(new MenuOptionDrawer(label));
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
  int y = 0;
  int x = this->width / 2;

  init_pair(1, COLOR_YELLOW, COLOR_BLACK);

  auto banner_data = std::read_file("assets/banner");

  attron(COLOR_PAIR(1));

  for (auto line : banner_data)
  {
    if (y >= this->height)
      break;

    mvprintw(y, x - line.length() / 2, line.c_str());

    y++;
  }

  init_pair(3, COLOR_WHITE, COLOR_BLACK);

  attron(COLOR_PAIR(3));

  y += 2;

  for (auto option : this->options)
  {
    if (y >= this->height)
      break;

    auto line = option->get_draw_label();

    mvprintw(y, x - line.length() / 2, line.c_str());

    y++;
  }

  y += 2;

  if (y < this->height)
  {
    std::string line = "Created by Gabriel Quintino 2023";

    init_pair(2, COLOR_BLUE, COLOR_BLACK);

    mvprintw(y, x - line.length() / 2, "Created by ");
    attron(COLOR_PAIR(2));
    printw("Gabriel Quintino");
    attron(COLOR_PAIR(3));
    printw(" 2023");
  }
}
// #endregion MenuDrawer
// #endregion Menus