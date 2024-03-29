#ifndef GRID_H
#define GRID_H

#include <vector>

#include <events/dispatcher.h>

#include "ptr.h"
#include "events.h"
#include "cell.h"

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
  EventDispatcher<GridStateEvent> *state;

  Grid(int width, int height);
  ~Grid();

  GridCell *get_cell(int x, int y);
  std::vector<GridCell *> get_cells();
  bool place_bomb_at(int x, int y);
  std::vector<GridCell *> get_neighbors(int x, int y);
  void place_bombs(int amount);
  void reveal();
  void reveal_at(int x, int y);
  void reveal_all(bool won);
  void flag();
  void flag_at(int x, int y);
  void focus(int x, int y);
  void check_state();
  std::string to_save();
  void from_save(std::string data);

private:
  /// @brief Current cell in focus by the pointer.
  GridCell *focused;
  /// @brief Collection of cells this grid contains.
  std::vector<GridCell *> cells;
  /// @brief List of cells that contains a bomb.
  std::vector<GridCell *> bombs;
  /// @brief List of cells that are empty.
  std::vector<GridCell *> safe_cells;
};

#endif
