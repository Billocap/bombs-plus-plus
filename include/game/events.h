#ifndef GAME_EVENTS_H
#define GAME_EVENTS_H

#include <events/handler.h>
#include <events/events.h>
#include <grid/events.h>

class Game;

class GameRenderHandler : public IEventHandler<RenderEvent>
{
public:
  GameRenderHandler(Game *game);

  void notify(RenderEvent *event);

private:
  Game *game;
};

class GameKeyboardHandler : public IEventHandler<KeyboardEvent>
{
public:
  GameKeyboardHandler(Game *game);

  void notify(KeyboardEvent *event);

private:
  Game *game;
};

class GridStateHandler : public IEventHandler<GridStateEvent>
{
public:
  GridStateHandler(Game *game);

  void notify(GridStateEvent *event);

private:
  Game *game;
};

#endif
