#ifndef GRID_UI_H
#define GRID_UI_H

#include <ncurses.h>

#include "grid.h"

/// @brief Class for rendering a grid.
class GridDrawer
{
public:
  void draw(std::Grid *grid);
};

#endif
