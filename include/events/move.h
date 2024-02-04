#ifndef MOVEMENT_EVENT_H
#define MOVEMENT_EVENT_H

#include <vector>

#include "events.h"

class MovementEvent;

/// @brief Utility type for a movement handler.
typedef IEventHandler<MovementEvent> MovementHandler;

/// @brief Class for an event that triggers when the coordinates of an object changes.
class MovementEvent
{
public:
  /// @brief The new X coordinate.
  int x;
  /// @brief The new Y coordinate.
  int y;

  MovementEvent(int x, int y);
};

/// @brief Class that triggers movement events.
class MovementDispatcher : public IEventDispatcher<MovementEvent>
{
public:
  void subscribe(MovementHandler *handler);
  void unsubscribe(MovementHandler *handler);
  void notify(MovementEvent *event);
};

#endif
