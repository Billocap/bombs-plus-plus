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
class TextBanner : public IDrawer
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
  void resize_clip_box(int height, int width){};
  void focus();
  void blur();

private:
  bool is_focused = false;
  int x;
  int y;
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
  void resize_clip_box(int height, int width){};
  void focus(int x, int y);
  void blur(int x, int y);

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
  void resize_clip_box(int height, int width){};

private:
  /// @brief Text label to be printed.
  std::string label;
  /// @brief Boolean that represents if this option is in focus.
  bool is_focused;
};

class MenuDrawer : public IDrawer
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
  int focused;
  /// @brief List of options this menu has.
  std::vector<MenuOptionDrawer *> options;
};

// #endregion Menus

#endif
