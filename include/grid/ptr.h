#ifndef GRID_POINTER_H
#define GRID_POINTER_H

#include <events/move.h>

#include "grid.h"
#include "cell.h"

namespace std
{
  class Grid;

  /// @brief The grid pointer marks the current selected cell.
  class GridPointer
  {
  public:
    MovementDispatcher *movement;

    GridPointer(Grid *parent);

    void go_left();
    void go_right();
    void go_up();
    void go_down();
    GridCell *get_cell();

  private:
    /// @brief Pointers X coordinate.
    int x = 0;
    /// @brief Pointers Y coordinate.
    int y = 0;

    /// @brief Grid object this pointer belongs to.
    Grid *parent;
  };
}

#endif
