#include <grid/cell.h>
#include <grid/events.h>
#include <grid/grid.h>
#include <grid/ptr.h>
#include <grid/render.h>

// #region GridStateEvent

GridStateEvent::GridStateEvent(bool won)
{
  this->won = won;
}

void GridStateDispatcher::subscribe(IEventHandler<GridStateEvent> *handler)
{
  this->handlers.push_back(handler);

  handler->id = this->handlers.size();
}

void GridStateDispatcher::unsubscribe(IEventHandler<GridStateEvent> *handler)
{
  auto it = this->handlers.begin() + handler->id;

  this->handlers.erase(it);
}

void GridStateDispatcher::notify(GridStateEvent *event)
{
  for (auto handler : this->handlers)
  {
    handler->notify(event);
  }
}

// #endregion GridStateEvent

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
/// @return The pointer to the current selected cell.
GridCell *GridPointer::get_cell()
{
  return this->parent->get_cell(this->x, this->y);
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

GridRenderHandler::GridRenderHandler(Grid *grid)
{
  this->grid = grid;
}

void GridRenderHandler::notify(RenderEvent *event)
{
  render_grid(this->grid, event);
}

PointerMovementHandler::PointerMovementHandler(Grid *grid)
{
  this->grid = grid;
}

void PointerMovementHandler::notify(MovementEvent *event)
{
  this->grid->focus();
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
  this->cells = std::vector<GridCell *>();
  this->focused = NULL;

  this->state = new GridStateDispatcher();

  this->on_key_press = new GridKeyboardHandler(this);
  this->on_render = new GridRenderHandler(this);

  this->pointer->movement->subscribe(new PointerMovementHandler(this));

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

/// @brief Returns a list of all the cells in this grid.
/// @return A vector containing all the cells.
std::vector<GridCell *> Grid::get_cells()
{
  return this->cells;
}

/// @brief Gets all the cells the neighbors the specified cell.
/// @param x X coordinate of the cell to get the neighbors.
/// @param y Y coordinate of the cell to get the neighbors.
/// @return A vector containing the neighbors.
std::vector<GridCell *> Grid::get_neighbors(int x, int y)
{
  std::vector<GridCell *> neighborhood;

  for (auto x_off = -1; x_off < 2; x_off++)
  {
    for (auto y_off = -1; y_off < 2; y_off++)
    {
      if (x_off != 0 || y_off != 0)
      {
        auto _x = x + x_off;
        auto _y = y + y_off;

        if (_x >= 0 && _y >= 0 && _x < this->width && _y < this->height)
        {
          neighborhood.push_back(this->get_cell(_x, _y));
        }
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

  for (auto cell : this->cells)
  {
    if (cell->has_bomb)
    {
      this->bombs.push_back(cell);
    }
    else
    {
      this->safe_cells.push_back(cell);
    }
  }
}

/// @brief Runs the reveal algorithm.
void Grid::reveal()
{
  std::vector<GridCell *> frontier;

  frontier.push_back(this->pointer->get_cell());

  while (!frontier.empty())
  {
    auto cell = frontier.back();

    frontier.pop_back();

    auto was_revealed = cell->reveal();

    if (was_revealed)
    {
      if (cell->has_bomb)
      {
        this->reveal_all(false);
        this->state->notify(new GridStateEvent(false));

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

  this->check_state();
}

/// @brief Reveal algorithm for when the game is over.
void Grid::reveal_all(bool won)
{
  if (won)
  {
    for (auto cell : this->safe_cells)
      cell->reveal();
  }
  else
  {
    for (auto cell : this->bombs)
      cell->reveal();
  }
}

/// @brief Flags the cell selected by the pointer.
void Grid::flag()
{
  this->pointer->get_cell()->flag();
}

/// @brief Verifies if all the bombs where flagged of all the safe cells were revelled.
void Grid::check_state()
{
  // Verifies that all bombs were flagged.
  bool all_flagged = true;

  for (auto bomb : this->bombs)
  {
    if (!bomb->has_flag)
      all_flagged = false;
  }

  if (all_flagged)
  {
    this->reveal_all(false);
    this->state->notify(new GridStateEvent(true));
  }

  // Verifies that all safe squares were revealed.
  bool all_revealed = true;

  for (auto cell : this->safe_cells)
  {
    if (!cell->is_revealed)
      all_revealed = false;
  }

  if (all_revealed)
  {
    this->reveal_all(false);
    this->state->notify(new GridStateEvent(true));
  }
}

/// @brief Puts the cell pointed by this grid's pointer in focus.
void Grid::focus()
{
  if (this->focused != NULL)
  {
    this->focused->is_focused = false;
  }

  this->focused = this->pointer->get_cell();
  this->focused->is_focused = true;
}

void Grid::flag_at(int x, int y)
{
  this->get_cell(x, y)->flag();
}

void Grid::reveal_at(int x, int y)
{
  this->get_cell(x, y)->reveal();
}

std::string Grid::to_save()
{
  std::string data;

  data += this->width;
  data += this->height;

  for (auto y = 0; y < this->height; y++)
  {
    for (auto x = 0; x < this->width; x++)
    {
      auto cell = this->get_cell(x, y);

      auto state = (cell->has_bomb << 2) | (cell->has_flag << 1) | cell->is_revealed;

      data += state + 8;
    }
  }

  return data;
}

void Grid::from_save(std::string data)
{
  int width = data[0];
  int height = data[1];

  this->width = width;
  this->height = height;

  this->cells.clear();
  this->bombs.clear();
  this->safe_cells.clear();

  for (auto y = 0; y < height; y++)
  {
    for (auto x = 0; x < width; x++)
    {
      auto c = new GridCell(x, y);

      this->cells.push_back(c);
    }
  }

  for (auto y = 0; y < height; y++)
  {
    for (auto x = 0; x < width; x++)
    {
      int state = data[2 + y * width + x];

      if (state & 4)
        this->place_bomb_at(x, y);

      if (state & 2)
      {
        this->flag_at(x, y);
      }
      else if (state & 1)
      {
        this->reveal_at(x, y);
      }
    }
  }

  for (auto cell : this->cells)
  {
    if (cell->has_bomb)
    {
      this->bombs.push_back(cell);
    }
    else
    {
      this->safe_cells.push_back(cell);
    }
  }
}

// #endregion Grid

/// @brief Renders a grid cell when a render event is triggered.
/// @param cell Pointer to the grid cell to render.
/// @param event Render event that triggered the render.
void render_cell(GridCell *cell, RenderEvent *event)
{
  if (cell->is_focused)
    attron(A_DIM);

  int x = event->x + cell->x * 2;
  int y = event->y + cell->y;

  if (cell->is_revealed)
  {
    auto bomb_count = cell->bomb_count;

    std::string lft_side[] = {" ", "¹", "²", "³", "⁴", "⁵", "⁶", "⁷", "⁸", "("};
    std::string rgt_side[] = {" ", "₁", "₂", "₃", "₄", "₅", "₆", "₇", "₈", ")"};

    std::string label = lft_side[bomb_count] + rgt_side[bomb_count];

    attron(COLOR_PAIR(100 + bomb_count));

    mvprintw(y, x, label.c_str());

    attroff(COLOR_PAIR(100 + bomb_count));
  }
  else
  {
    attron(COLOR_PAIR(100));

    mvprintw(y, x, cell->has_flag ? " ╕" : "░░");

    attron(COLOR_PAIR(100));
  }

  if (cell->is_focused)
    attroff(A_DIM);
};

/// @brief Render a grid object when a render event is triggered.
/// @param grid Pointer to the grid to render.
/// @param event Render event that triggered the render.
void render_grid(Grid *grid, RenderEvent *event)
{
  // Necessary for printing wide chars.
  attron(A_ALTCHARSET);

  // Initialize the color pairs.
  init_pair(100, COLOR_WHITE, COLOR_BLACK);  // 0
  init_pair(101, COLOR_GREEN, COLOR_BLACK);  // 1
  init_pair(102, COLOR_BLUE, COLOR_BLACK);   // 2
  init_pair(103, COLOR_YELLOW, COLOR_BLACK); // 3
  init_pair(104, COLOR_YELLOW, COLOR_BLACK); // 4
  init_pair(105, COLOR_RED, COLOR_BLACK);    // 5
  init_pair(106, COLOR_RED, COLOR_BLACK);    // 6
  init_pair(107, COLOR_RED, COLOR_BLACK);    // 7
  init_pair(108, COLOR_RED, COLOR_BLACK);    // 8
  init_pair(109, COLOR_RED, COLOR_BLACK);    // Has bomb

  for (auto cell : grid->get_cells())
  {
    auto cell_event = new RenderEvent(event->width, event->height, event->x - grid->width, event->y);

    render_cell(cell, cell_event);
  }

  attroff(A_ALTCHARSET);
};
