#ifndef UI_H
#define UI_H

#include <vector>
#include <string>
#include <ncurses.h>

#include "grid.h"
#include "io.h"

/// @brief Class for rendering a grid.
class GridDrawer
{
public:
  void draw(std::Grid *grid);
};

// #region Menus
/// @brief Represents all the state for one option.
class MenuOptionDrawer
{
public:
  MenuOptionDrawer(std::string label);

  std::string get_draw_label();
  void focus();
  void blur();

private:
  /// @brief Text label to be printed.
  std::string label;
  /// @brief Boolean that represents if this option is in focus.
  bool is_focused;
};

class MenuDrawer
{
public:
  void add_option(std::string label);
  void focus(int id);
  void blur(int id);
  void draw();

private:
  /// @brief Current option in focus.
  int focused = -1;
  /// @brief List of options this menu has.
  std::vector<MenuOptionDrawer *> options;
};
// #endregion Menus

#endif
