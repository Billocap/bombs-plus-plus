#include "grid.h"

namespace std
{
  // #region GridCell
  /// @brief Creates a nes cell at the specified coordinates.
  /// @param parent Grid object that contains this cell.
  /// @param x X position on the grid.
  /// @param y Y position on the grid.
  GridCell::GridCell(Grid *parent, int x, int y)
  {
    this->parent = parent;
    this->x = x;
    this->y = y;
  }
  // #endregion GridCell

  // #region Grid
  /// @brief Creates a new grid with the specified size.
  /// @param width Width for the grid.
  /// @param height Height for the grid.
  Grid::Grid(int width, int height)
  {
    this->width = width;
    this->height = height;
    this->cells = vector<GridCell *>();

    srand((unsigned)time(NULL));

    for (auto y = 0; y < height; y++)
    {
      for (auto x = 0; x < width; x++)
      {
        auto c = new GridCell(this, x, y);

        this->cells.push_back(c);
      }
    }
  }

  /// @brief Returns the GridCell at the specified position.
  /// @param x X coordinate for the cell.
  /// @param y Y coordinate for the cell.
  /// @return A pointer for the desired cell.
  GridCell *Grid::get_cell(int x, int y)
  {
    int i = y * this->width + x;

    return this->cells[i];
  }

  /// @brief Places a bomb in the specified grid position.
  /// @param x X coordinate to place the bomb in.
  /// @param y Y coordinate to place the bomb in.
  /// @returns A boolean that defines if the bomb was placed.
  bool Grid::place_bomb_at(int x, int y)
  {
    auto c = this->get_cell(x, y);

    if (c->has_bomb)
    {
      return false;
    }
    else
    {
      c->has_bomb = true;

      for (auto x_off = -1; x_off < 2; x_off++)
      {
        for (auto y_off = -1; y_off < 2; y_off++)
        {
          auto _x = x + x_off;
          auto _y = y + y_off;

          if (_x >= 0 && _y >= 0 && _x < this->width && _y < this->height)
          {
            auto c = this->get_cell(_x, _y);

            c->bomb_count++;
          }
        }
      }

      return true;
    }
  }

  /// @brief Place a certain amount of bombs in random positions.
  /// @param amount Number of bombs to place.
  void Grid::place_bombs(int amount)
  {
    int n = 0;

    while (n < amount)
    {
      int x = rand() % this->width;
      int y = rand() % this->height;

      while (!this->place_bomb_at(x, y))
      {
        x = rand() % this->width;
        y = rand() % this->height;
      }

      n++;
    }
  }
  // #endregion Grid
}
