#include "gridui.h"

// #region GridDrawer
/// @brief Draws a grid to the console.
/// @param grid Pointer to the grid to be drawn.
void GridDrawer::draw(std::Grid *grid)
{
  for (auto y = 0; y < grid->height; y++)
  {
    for (auto x = 0; x < grid->width; x++)
    {
      move(y, x * 2);

      printw("[]");
    }
  }

  printw("\n");
}
// #endregion GridDrawer
