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

  /// @brief Places a on this cell.
  /// @return Boolean that tells if the state changed.
  bool GridCell::flag()
  {
    if (!this->is_revealed)
    {
      this->has_flag = !this->has_flag;

      return true;
    }

    return false;
  }

  /// @brief Reveal this cell.
  /// @return Boolean that tells if the state changed.
  bool GridCell::reveal()
  {
    if (!this->has_flag)
    {
      this->is_revealed = true;

      return true;
    }

    return false;
  }

  // #endregion GridCell

  // #region GridPointer

  /// @brief Creates a new grid pointer.
  /// @param parent Grid object that contains this pointer.
  GridPointer::GridPointer(Grid *parent)
  {
    this->parent = parent;
    this->movement = new MovementDispatcher();
  }

  /// @brief Moves the pointer up one cell.
  void GridPointer::go_up()
  {
    this->y = (this->parent->height + this->y - 1) % this->parent->height;

    this->movement->notify(new MovementEvent(this->x, this->y));
  }

  /// @brief Moves the pointer down one cell.
  void GridPointer::go_down()
  {
    this->y = (this->y + 1) % this->parent->height;

    this->movement->notify(new MovementEvent(this->x, this->y));
  }

  /// @brief Moves the pointer left one cell.
  void GridPointer::go_left()
  {
    this->x = (this->parent->width + this->x - 1) % this->parent->width;

    this->movement->notify(new MovementEvent(this->x, this->y));
  }

  /// @brief Moves the pointer right one cell.
  void GridPointer::go_right()
  {
    this->x = (this->x + 1) % this->parent->width;

    this->movement->notify(new MovementEvent(this->x, this->y));
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

  // #region GridKeyboardHandler

  GridKeyboardHandler::GridKeyboardHandler(Grid *grid)
  {
    this->grid = grid;
  }

  void GridKeyboardHandler::notify(KeyboardEvent *event)
  {
    switch (event->key)
    {
    case IO_KEY_UP:
      this->grid->pointer->go_up();
      break;

    case IO_KEY_DOWN:
      this->grid->pointer->go_down();
      break;

    case IO_KEY_LEFT:
      this->grid->pointer->go_left();
      break;

    case IO_KEY_RIGHT:
      this->grid->pointer->go_right();
      break;

    case IO_KEY_CONFIRM:
      this->grid->reveal();
      break;

    case IO_KEY_ACCENT:
      this->grid->flag();
      break;
    }
  }

  PointerMovementHandler::PointerMovementHandler(GridDrawer *drawer)
  {
    this->drawer = drawer;
  }

  void PointerMovementHandler::notify(MovementEvent *event)
  {
    // this->drawer->focus(event->x, event->y);
  }

  // #endregion GridKeyboardHandler

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
    this->on_key_press = new GridKeyboardHandler(this);

    this->pointer->movement->subscribe(new PointerMovementHandler(this->drawer));

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

  /// @brief Gets all the cells the neighbors the specified cell.
  /// @param x X coordinate of the cell to get the neighbors.
  /// @param y Y coordinate of the cell to get the neighbors.
  /// @return A vector containing the neighbors.
  vector<GridCell *> Grid::get_neighbors(int x, int y)
  {
    vector<GridCell *> neighborhood;

    for (auto x_off = -1; x_off < 2; x_off++)
    {
      for (auto y_off = -1; y_off < 2; y_off++)
      {
        if (x_off == 0 && y_off == 0)
          continue;

        auto _x = x + x_off;
        auto _y = y + y_off;

        if (_x >= 0 && _y >= 0 && _x < this->width && _y < this->height)
        {
          neighborhood.push_back(this->get_cell(_x, _y));
        }
      }
    }

    return neighborhood;
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
      c->bomb_count = 9;

      for (auto neighbor : this->get_neighbors(x, y))
      {
        if (!neighbor->has_bomb)
          neighbor->bomb_count++;
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

    // for (auto cell : this->cells)
    // {
    //   if (cell->has_bomb)
    //   {
    //     this->bombs.push_back(cell);
    //   }
    //   else
    //   {
    //     this->safe_cells.push_back(cell);
    //   }
    // }
  }

  /// @brief Runs the reveal algorithm.
  void Grid::reveal()
  {
    vector<GridCell *> frontier;

    frontier.push_back(this->pointer->get_cell());

    while (!frontier.empty())
    {
      auto cell = frontier.back();

      frontier.pop_back();

      auto was_revealed = cell->reveal();

      if (was_revealed)
      {
        this->drawer->reveal(cell->x, cell->y, cell->bomb_count, cell->has_bomb);

        if (cell->has_bomb)
        {
          this->exploded = true;

          break;
        }

        auto neighbors = this->get_neighbors(cell->x, cell->y);

        if (cell->bomb_count == 0)
        {
          for (auto neighbor : neighbors)
          {
            if (!neighbor->is_revealed)
              frontier.push_back(neighbor);
          }
        }
        else
        {
          int flagged = 0;

          for (auto neighbor : neighbors)
          {
            if (neighbor->has_flag)
              flagged++;
          }

          if (flagged == cell->bomb_count)
          {
            for (auto neighbor : neighbors)
            {
              if (!neighbor->is_revealed)
                frontier.push_back(neighbor);
            }
          }
        }
      }
    }

    // bool all_flagged = true;

    // for (auto bomb : this->bombs)
    // {
    //   if (!bomb->has_flag)
    //     all_flagged = false;
    // }

    // if (all_flagged)
    //   this->completed = true;

    // bool all_revealed = true;

    // for (auto cell : this->safe_cells)
    // {
    //   if (!cell->is_revealed)
    //     all_revealed = false;
    // }

    // if (all_revealed)
    //   this->completed = true;
  }

  /// @brief Flags the cell selected by the pointer.
  void Grid::flag()
  {
    auto was_flagged = this->pointer->get_cell()->flag();

    if (was_flagged)
    {
      this->drawer->flag(this->pointer->get_x(), this->pointer->get_y());
    }
  }

  // #endregion Grid
}
