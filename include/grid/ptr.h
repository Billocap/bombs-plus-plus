#ifndef GRID_POINTER_H
#define GRID_POINTER_H

#include <events/dispatcher.h>
#include <events/events.h>

#include "grid.h"
#include "cell.h"

class Grid;

/// @brief The grid pointer marks the current selected cell.
class GridPointer
{
public:
  EventDispatcher<MovementEvent> *movement;

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

#endif
