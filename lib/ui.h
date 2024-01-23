#ifndef UI_H
#define UI_H

#include <vector>
#include <string>
#include <ncursesw/ncurses.h>

#include "io.h"

// #region Interfaces

/// @brief Interface for a drawer class.
class IDrawer
{
public:
  /// @brief Draws this object in the specified position.
  /// @param y Y position to draw the option at.
  /// @param x X position to draw the option at.
  /// @return The updated Y position.
  virtual int draw(int y, int x) = 0;
};

/// @brief Interface for a drawer class that can be resized.
class IResizableDrawer : public IDrawer
{
public:
  /// @brief Defines the max `width` and `height`.
  /// @param height Max height.
  /// @param width Max width.
  virtual void resize_clip_box(int height, int width) = 0;

protected:
  /// @brief Maximum width.
  int clip_width = 0;
  /// @brief Maximum height.
  int clip_height = 0;
};

// #endregion Interfaces

// #region Banner

/// @brief Text banner are used to improve the UI.
class TextBanner : public IResizableDrawer
{
public:
  TextBanner(std::string file);

  int draw(int y, int x);
  void resize_clip_box(int height, int width);

private:
  /// @brief Actual data contained in the banner file.
  std::vector<std::string> data;
};

// #endregion Banner

// #region Grid

class GridCellDrawer : public IDrawer
{
public:
  GridCellDrawer(int x, int y);

  int draw(int y, int x);
  void focus();
  void blur();
  void flag();
  void reveal(int count, bool has_bomb);

private:
  bool is_focused = false;
  int x;
  int y;
  /// @brief Boolean that defines if the cell has a bomb.
  bool has_bomb = false;
  /// @brief Boolean that defines if the cell has a flag.
  bool has_flag = false;
  /// @brief Boolean that defines if the cell was revealed.
  bool is_revealed = false;
  /// @brief How many neighbors of this cell has a bomb.
  int bomb_count = 0;
};

/// @brief Class for rendering a grid.
class GridDrawer : public IDrawer
{
public:
  /// @brief Width of the grid in cells.
  int width;
  /// @brief Height of the grid in cells.
  int height;

  GridDrawer(int width, int height);

  int draw(int y, int x);
  void focus(int x, int y);
  void blur(int x, int y);
  void flag(int x, int y);
  void reveal(int x, int y, int count, bool has_bomb);

private:
  std::vector<GridCellDrawer *> cells;
  GridCellDrawer *focused;
};

// #endregion Grid

// #region Menus

class MenuDrawer;

/// @brief Represents all the state for one option.
class MenuOptionDrawer : public IDrawer
{
public:
  MenuOptionDrawer(std::string label);

  void focus();
  void blur();
  int draw(int y, int x);

private:
  /// @brief Text label to be printed.
  std::string label;
  /// @brief Boolean that represents if this option is in focus.
  bool is_focused = false;
};

class MenuDrawer : public IResizableDrawer
{
public:
  void add_option(std::string label);
  void focus(int id);
  void blur(int id);
  int draw(int y, int x);
  void resize_clip_box(int height, int width);
  void set_banner(TextBanner *banner);

private:
  /// @brief The main banner for this menu.
  TextBanner *banner;
  /// @brief Current option in focus.
  MenuOptionDrawer *focused;
  /// @brief List of options this menu has.
  std::vector<MenuOptionDrawer *> options;
};

// #endregion Menus

#endif
