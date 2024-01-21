#ifndef GRID_H
#define GRID_H

#include <vector>
#include <cstdlib>
#include <time.h>

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

    GridCell(Grid *parent, int x, int y);

  private:
    /// @brief Grid object that contains this cell.
    Grid *parent;
  };

  /// @brief A grid is a collection of tiles.
  class Grid
  {
  public:
    /// @brief Width of the grid in cells.
    int width;
    /// @brief Height of the grid in cells.
    int height;

    Grid(int width, int height);

    GridCell *get_cell(int x, int y);
    bool place_bomb_at(int x, int y);
    void place_bombs(int amount);

  private:
    /// @brief Collection of cells this grid contains.
    vector<GridCell *> cells;
  };
}

#endif
