#ifndef RENDER_EVENT_H
#define RENDER_EVENT_H

#include <vector>

#include "events.h"

class RenderEvent;

/// @brief Utility type for render event handlers.
typedef IEventHandler<RenderEvent> RenderHandler;

/// @brief Class for events that draws to the viewport.
class RenderEvent
{
public:
  /// @brief Width of the viewport.
  int width;
  /// @brief Height of the viewport.
  int height;
  /// @brief X coordinate to draw at.
  int x;
  /// @brief Y coordinate to draw at.
  int y;

  RenderEvent(int width, int height, int x, int y);
};

/// @brief Class that triggers render events.
class RenderDispatcher : public IEventDispatcher<RenderEvent>
{
public:
  void subscribe(RenderHandler *handler);
  void unsubscribe(RenderHandler *handler);
  void notify(RenderEvent *event);
};

#endif
