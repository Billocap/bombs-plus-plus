#ifndef UI_H
#define UI_H

#include <vector>
#include <string>
#include <ncurses.h>

#include "io.h"

// #region Interfaces

/// @brief Interface for a drawer class.
class IDrawer
{
public:
  /// @brief Draws this object.
  virtual void draw() = 0;
};

/// @brief Interface for the childs of a Drawer class.
class IChildDrawer
{
public:
  /// @brief Draws this child in the specified position.
  /// @param y Y position to draw the option at.
  /// @param x X position to draw the option at.
  /// @return The updated Y position.
  virtual int draw(int y, int x) = 0;
};

// #endregion Interfaces

/// @brief Class for rendering a grid.
class GridDrawer : public IDrawer
{
public:
  /// @brief Width of the grid in cells.
  int width;
  /// @brief Height of the grid in cells.
  int height;

  GridDrawer(int width, int height);

  void draw();
};

// #region Menus

class MenuDrawer;

/// @brief Represents all the state for one option.
class MenuOptionDrawer : public IChildDrawer
{
public:
  MenuOptionDrawer(MenuDrawer *parent, std::string label);

  void focus();
  void blur();
  int draw(int y, int x);

private:
  /// @brief Text label to be printed.
  std::string label;
  /// @brief Boolean that represents if this option is in focus.
  bool is_focused;
  MenuDrawer *parent;
};

class MenuDrawer : public IDrawer
{
public:
  int width;
  int height;

  void add_option(std::string label);
  void focus(int id);
  void blur(int id);
  void draw();

private:
  /// @brief Current option in focus.
  int focused;
  /// @brief List of options this menu has.
  std::vector<MenuOptionDrawer *> options;
};

// #endregion Menus

#endif
