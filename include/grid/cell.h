#ifndef GRID_CELL_H
#define GRID_CELL_H

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
  /// @brief Boolean that defines if the cell has a flag.
  bool has_flag = false;
  /// @brief Boolean that defines if the cell was revealed.
  bool is_revealed = false;
  /// @brief If the cell is in focus.
  bool is_focused = false;
  /// @brief How many neighbors of this cell has a bomb.
  int bomb_count = 0;

  GridCell(int x, int y);

  bool flag();
  bool reveal();
};

#endif
