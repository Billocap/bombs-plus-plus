#ifndef GRID_H
#define GRID_H

#include <vector>
#include <cstdlib>
#include <time.h>
#include <ncursesw/ncurses.h>
#include <string>

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
    PointerMovementHandler(Grid *grid);

    void notify(MovementEvent *event);

  private:
    Grid *grid;
  };

  class GridStateEvent
  {
  public:
    bool won;

    GridStateEvent(bool won);
  };

  class GridStateDispatcher : public IEventDispatcher<GridStateEvent>
  {
  public:
    void subscribe(IEventHandler<GridStateEvent> *handler);
    void unsubscribe(IEventHandler<GridStateEvent> *handler);
    void notify(GridStateEvent *event);

  private:
    vector<IEventHandler<GridStateEvent> *> handlers;
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
    /// @brief If the cell is in focus.
    bool is_focused = false;
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
    /// @brief Keyboard event handler.
    GridKeyboardHandler *on_key_press;
    /// @brief Render event handler.
    GridRenderHandler *on_render;
    /// @brief Width of the grid in cells.
    int width;
    /// @brief Height of the grid in cells.
    int height;
    /// @brief Grid pointer keeps track of the current selected cell.
    GridPointer *pointer;
    /// @brief Event dispatcher for grid state changes.
    GridStateDispatcher *state;

    Grid(int width, int height);

    GridCell *get_cell(int x, int y);
    vector<GridCell *> get_cells();
    bool place_bomb_at(int x, int y);
    vector<GridCell *> get_neighbors(int x, int y);
    void place_bombs(int amount);
    void reveal();
    void reveal_all(bool won);
    void flag();
    void focus();
    void check_state();

  private:
    /// @brief Current cell in focus by the pointer.
    GridCell *focused;
    /// @brief Collection of cells this grid contains.
    vector<GridCell *> cells;
    /// @brief List of cells that contains a bomb.
    vector<GridCell *> bombs;
    /// @brief List of cells that are empty.
    vector<GridCell *> safe_cells;
  };
}

void render_cell(std::GridCell *cell, std::RenderEvent *event);
void render_grid(std::Grid *grid, std::RenderEvent *event);

#endif
