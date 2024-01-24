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

// #region Grid
// #region GridDrawer

/// @brief Creates a new grid drawer.
/// @param width This grids width.
/// @param height This grids height.
GridDrawer::GridDrawer(int width, int height)
{
  this->width = width;
  this->height = height;

  for (auto y = 0; y < height; y++)
  {
    for (auto x = 0; x < width; x++)
    {
      auto c = new GridCellDrawer(x, y);

      this->cells.push_back(c);
    }
  }
}

/// @brief Draws this grid in the specified position.
/// @param y Y position to draw at.
/// @param x X position to draw at.
/// @return The updated Y position.
int GridDrawer::draw(int y, int x)
{
  attron(A_ALTCHARSET);

  init_pair(100, COLOR_WHITE, COLOR_BLACK);  // 0
  init_pair(101, COLOR_GREEN, COLOR_BLACK);  // 1
  init_pair(102, COLOR_BLUE, COLOR_BLACK);   // 2
  init_pair(103, COLOR_YELLOW, COLOR_BLACK); // 3
  init_pair(104, COLOR_YELLOW, COLOR_BLACK); // 4
  init_pair(105, COLOR_RED, COLOR_BLACK);    // 5
  init_pair(106, COLOR_RED, COLOR_BLACK);    // 6
  init_pair(107, COLOR_RED, COLOR_BLACK);    // 7
  init_pair(108, COLOR_RED, COLOR_BLACK);    // 8
  init_pair(109, COLOR_RED, COLOR_BLACK);    // Has bomb

  for (auto cell : this->cells)
  {
    cell->draw(y, x - this->width);
  }

  mvprintw(x, y - 1, "Bombs left: ");

  attroff(A_ALTCHARSET);

  return y + 1;
}

void GridDrawer::focus(int x, int y)
{
  if (this->focused != NULL)
  {
    this->focused->blur();
  }

  int i = y * this->width + x;

  this->cells[i]->focus();
  this->focused = this->cells[i];
}

void GridDrawer::blur(int x, int y)
{
  if (this->focused != NULL)
  {
    this->focused->blur();
  }

  this->focused = NULL;
}

void GridDrawer::flag(int x, int y)
{
  int i = y * this->width + x;

  this->cells[i]->flag();
}

void GridDrawer::reveal(int x, int y, int count, bool has_bomb)
{
  int i = y * this->width + x;

  this->cells[i]->reveal(count, has_bomb);
}

// #endregion GridDrawer

// #region GridCellDrawer

GridCellDrawer::GridCellDrawer(int x, int y)
{
  this->x = x;
  this->y = y;
}

int GridCellDrawer::draw(int y, int x)
{
  if (this->is_focused)
    attron(A_DIM);

  if (this->is_revealed)
  {
    auto bomb_count = this->bomb_count;

    std::string lft_side[] = {" ", "¹", "²", "³", "⁴", "⁵", "⁶", "⁷", "⁸", "("};
    std::string rgt_side[] = {" ", "₁", "₂", "₃", "₄", "₅", "₆", "₇", "₈", ")"};

    std::string label = lft_side[bomb_count] + rgt_side[bomb_count];

    attron(COLOR_PAIR(100 + bomb_count));

    mvprintw(y + this->y, x + this->x * 2, label.c_str());

    attroff(COLOR_PAIR(100 + bomb_count));
  }
  else
  {
    attron(COLOR_PAIR(100));

    mvprintw(y + this->y, x + this->x * 2, this->has_flag ? " ╕" : "░░");

    attron(COLOR_PAIR(100));
  }

  if (this->is_focused)
    attroff(A_DIM);

  return 0;
}

void GridCellDrawer::focus()
{
  this->is_focused = true;
}

void GridCellDrawer::blur()
{
  this->is_focused = false;
}

void GridCellDrawer::flag()
{
  this->has_flag = !this->has_flag;
}

void GridCellDrawer::reveal(int count, bool has_bomb)
{
  this->is_revealed = true;
  this->bomb_count = count;
  this->has_bomb = has_bomb;
}

// #region GridCellDrawer
// #endregion Grid

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