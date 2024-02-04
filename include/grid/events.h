#ifndef GRID_EVENTS_H
#define GRID_EVENTS_H

#include <events/events.h>
#include <events/kbd.h>
#include <events/move.h>
#include <events/render.h>
#include <io.h>

class Grid;

// #region Handlers

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

// #endregion Handlers

// #region Events

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
};

// #endregion Events

#endif
