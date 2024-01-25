#ifndef GRID_H
#define GRID_H

#include <vector>
#include <cstdlib>
#include <time.h>

#include "ui.h"
#include "events.h"

namespace std
{
  class Grid;

  // #region Events

  class GridKeyboardHandler : public IEventHandler<KeyboardEvent>
  {
  public:
    GridKeyboardHandler(Grid *grid);

    void notify(KeyboardEvent *event);

  private:
    Grid *grid;
  };

  class GridRenderHandler : public IEventHandler<RenderEvent>
  {
  public:
    GridRenderHandler(Grid *grid);

    void notify(RenderEvent *event);

  private:
    Grid *grid;
  };

  class PointerMovementHandler : public IEventHandler<MovementEvent>
  {
  public:
    PointerMovementHandler(GridDrawer *drawer);

    void notify(MovementEvent *event);

  private:
    GridDrawer *drawer;
  };

  // #endregion Events

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
    /// @brief How many neighbors of this cell has a bomb.
    int bomb_count = 0;

    GridCell(int x, int y);

    bool flag();
    bool reveal();
  };

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
  class Grid
  {
  public:
    /// @brief Renderer for this grid.
    GridDrawer *drawer;
    GridKeyboardHandler *on_key_press;
    GridRenderHandler *on_render;
    /// @brief Width of the grid in cells.
    int width;
    /// @brief Height of the grid in cells.
    int height;
    /// @brief Tells if a bomb was revealed.
    bool exploded = false;
    /// @brief Tells if all the cells were revealed.
    bool completed = false;
    /// @brief Grid pointer keeps track of the current selected cell.
    GridPointer *pointer;

    Grid(int width, int height);

    GridCell *get_cell(int x, int y);
    bool place_bomb_at(int x, int y);
    vector<GridCell *> get_neighbors(int x, int y);
    void place_bombs(int amount);
    void reveal();
    void flag();

  private:
    /// @brief Collection of cells this grid contains.
    vector<GridCell *> cells;

    GridCell *focused;

    // vector<GridCell *> bombs;
    // vector<GridCell *> safe_cells;
  };
}

#endif
