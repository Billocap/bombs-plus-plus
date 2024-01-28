#include "ui.h"

// #region TextBanner

/// @brief Creates a new text banner.
/// @param path Path to the file that contains the banner's data.
TextBanner::TextBanner(std::string path)
{
  this->data = std::read_file(path);
}

/// @brief Draws this banner in the specified position.
/// @param y Y position to draw at.
/// @param x X position to draw at.
/// @return The updated Y position.
int TextBanner::draw(int y, int x)
{
  int _y = 0;

  init_pair(100, COLOR_YELLOW, COLOR_BLACK);

  attron(COLOR_PAIR(100) | A_DIM);

  for (auto line : this->data)
  {
    if (_y >= this->clip_height)
      break;

    mvprintw(y + _y, x - line.length() / 2, line.c_str());

    _y++;
  }
  attroff(COLOR_PAIR(100) | A_DIM);

  return y + _y;
}

/// @brief Defines the max `width` and `height`.
/// @param height Max height.
/// @param width Max width.
void TextBanner::resize_clip_box(int height, int width)
{
  this->clip_width = width;
  this->clip_height = height;
}

// #endregion TextBanner

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
  this->options.push_back(new MenuOptionDrawer(label));
}

/// @brief Focus on the desired option.
/// @param id Id of the option to focus on.
void MenuDrawer::focus(int id)
{
  if (this->focused != NULL)
    this->focused->blur();

  this->options[id]->focus();
  this->focused = this->options[id];
}

/// @brief Makes the option out of focus.
/// @param id Id of the option to blur.
void MenuDrawer::blur(int id)
{
  if (this->focused != NULL)
    this->focused->blur();

  this->focused = NULL;
}

void MenuDrawer::resize_clip_box(int height, int width)
{
  if (this->banner != NULL)
    this->banner->resize_clip_box(height, width);

  this->clip_width = width;
  this->clip_height = height;
}

/// @brief Draws this menu in the specified position.
/// @param y Y coordinate to draw at.
/// @param x X coordinate to draw at.
/// @return The updated Y position.
int MenuDrawer::draw(int y, int x)
{
  if (this->banner != NULL)
    y = this->banner->draw(y, x);

  init_pair(1, COLOR_WHITE, COLOR_BLACK);

  attron(COLOR_PAIR(1));

  y += 2;

  for (auto option : this->options)
  {
    if (y >= this->clip_height)
      break;

    y = option->draw(y, x);
  }

  y += 2;

  if (y < this->clip_height)
  {
    std::string line = "Created by Gabriel Quintino";

    init_pair(2, COLOR_BLUE, COLOR_BLACK);

    mvprintw(y, x - line.length() / 2, "Created by ");
    attron(COLOR_PAIR(2));
    printw("Gabriel Quintino");
    attron(COLOR_PAIR(1));
  }

  return y + 1;
}

/// @brief Sets the banner for this menu.
/// @param banner The banner object.
void MenuDrawer::set_banner(TextBanner *banner)
{
  this->banner = banner;
}

// #endregion MenuDrawer
// #endregion Menus
