#ifndef GRID_RENDER_H
#define GRID_RENDER_H

#include <ncursesw/ncurses.h>

#include "grid.h"

void render_cell(std::GridCell *cell, std::RenderEvent *event);
void render_grid(std::Grid *grid, std::RenderEvent *event);

#endif
