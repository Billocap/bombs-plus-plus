#include "grid.h"

namespace std
{
  // #region GridCell

  /// @brief Creates a nes cell at the specified coordinates.
  /// @param x X position on the grid.
  /// @param y Y position on the grid.
  GridCell::GridCell(int x, int y)
  {
    this->x = x;
    this->y = y;
  }

  // #endregion GridCell

  // #region GridPointer

  /// @brief Creates a new grid pointer.
  /// @param parent Grid object that contains this pointer.
  GridPointer::GridPointer(Grid *parent)
  {
    this->parent = parent;
  }

  /// @brief Moves the pointer up one cell.
  void GridPointer::go_up()
  {
    this->y = (this->parent->height + this->y - 1) % this->parent->height;
  }

  /// @brief Moves the pointer down one cell.
  void GridPointer::go_down()
  {
    this->y = (this->y + 1) % this->parent->height;
  }

  /// @brief Moves the pointer left one cell.
  void GridPointer::go_left()
  {
    this->x = (this->parent->width + this->x - 1) % this->parent->width;
  }

  /// @brief Moves the pointer right one cell.
  void GridPointer::go_right()
  {
    this->x = (this->x + 1) % this->parent->width;
  }

  /// @brief Returns the current selected cell.
  /// @return O pointer to the current selected cell.
  GridCell *GridPointer::get_cell()
  {
    return this->parent->get_cell(this->x, this->y);
  }

  int GridPointer::get_x()
  {
    return this->x;
  }

  int GridPointer::get_y()
  {
    return this->y;
  }

  // #endregion GridPointer

  // #region Grid

  /// @brief Creates a new grid with the specified size.
  /// @param width Width for the grid.
  /// @param height Height for the grid.
  Grid::Grid(int width, int height)
  {
    this->width = width;
    this->height = height;
    this->pointer = new GridPointer(this);
    this->drawer = new GridDrawer(width, height);
    this->cells = vector<GridCell *>();

    srand((unsigned)time(NULL));

    for (auto y = 0; y < height; y++)
    {
      for (auto x = 0; x < width; x++)
      {
        auto c = new GridCell(x, y);

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
  /// @return A boolean that defines if the bomb was placed.
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

  /// @brief Handles keyboard input for a game grid.
  /// @param key ASCII code for the key pressed.
  void Grid::handle_input(int key)
  {
    switch (key)
    {
    case IO_KEY_UP:
      this->pointer->go_up();
      break;

    case IO_KEY_DOWN:
      this->pointer->go_down();
      break;

    case IO_KEY_LEFT:
      this->pointer->go_left();
      break;

    case IO_KEY_RIGHT:
      this->pointer->go_right();
      break;

    case IO_KEY_CONFIRM:
      this->pointer->get_cell();
      break;

    case IO_KEY_ACCENT:
      this->pointer->get_cell();
      break;
    }

    this->drawer->focus(this->pointer->get_x(), this->pointer->get_y());
  }

  // #endregion Grid
}
