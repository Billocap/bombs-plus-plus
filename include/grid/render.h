#ifndef GRID_RENDER_H
#define GRID_RENDER_H

#include <ncursesw/ncurses.h>

#include "grid.h"

void render_cell(GridCell *cell, RenderEvent *event);
void render_grid(Grid *grid, RenderEvent *event);

#endif
