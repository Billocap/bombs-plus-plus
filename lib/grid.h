#ifndef GRID_H
#define GRID_H

#include <vector>
#include <cstdlib>
#include <time.h>

#include "io.h"
#include "ui.h"

namespace std
{
  class Grid;

  /// @brief Represents a single tile on the grid.
  class GridCell
  {
  public:
    /// @brief X position on the grid.
    int x;
    /// @brief Y position on the grid
    int y;
    /// @brief Boolean that defines if the cell has a bomb.
    bool has_bomb = false;
    /// @brief How many neighbors of this cell has a bomb.
    int bomb_count = 0;

    GridCell(int x, int y);
  };

  /// @brief The grid pointer marks the current selected cell.
  class GridPointer
  {
  public:
    GridPointer(Grid *parent);

    void go_left();
    void go_right();
    void go_up();
    void go_down();
    GridCell *get_cell();
    int get_x();
    int get_y();

  private:
    /// @brief Pointers X coordinate.
    int x = 0;
    /// @brief Pointers Y coordinate.
    int y = 0;

    /// @brief Grid object this pointer belongs to.
    Grid *parent;
  };

  /// @brief A grid is a collection of tiles.
  class Grid : public IInputHandler
  {
  public:
    /// @brief Renderer for this grid.
    GridDrawer *drawer;
    /// @brief Width of the grid in cells.
    int width;
    /// @brief Height of the grid in cells.
    int height;

    Grid(int width, int height);

    GridCell *get_cell(int x, int y);
    bool place_bomb_at(int x, int y);
    void place_bombs(int amount);
    void handle_input(int key);

  private:
    /// @brief Collection of cells this grid contains.
    vector<GridCell *> cells;
    /// @brief Grid pointer keeps track of the current selected cell.
    GridPointer *pointer;
  };
}

#endif
