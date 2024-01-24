#include "events.h"

namespace std
{
  // #region KeyboardEvent

  KeyboardEvent::KeyboardEvent(int key)
  {
    this->key = key;
  }

  void KeyboardDispatcher::subscribe(KeyboardHandler *handler)
  {
    this->handlers.push_back(handler);

    handler->id = this->handlers.size();
  }

  void KeyboardDispatcher::unsubscribe(KeyboardHandler *handler)
  {
    auto it = this->handlers.begin() + handler->id;

    this->handlers.erase(it);
  }

  void KeyboardDispatcher::notify(KeyboardEvent *event)
  {
    for (auto handler : this->handlers)
    {
      handler->notify(event);
    }
  }

  // #endregion KeyboardEvent

  // #region RenderEvent

  RenderEvent::RenderEvent(int width, int height, int x, int y)
  {
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
  }

  void RenderDispatcher::subscribe(RenderHandler *handler)
  {
    this->handlers.push_back(handler);

    handler->id = this->handlers.size();
  }

  void RenderDispatcher::unsubscribe(RenderHandler *handler)
  {
    auto it = this->handlers.begin() + handler->id;

    this->handlers.erase(it);
  }

  void RenderDispatcher::notify(RenderEvent *event)
  {
    for (auto handler : this->handlers)
    {
      handler->notify(event);
    }
  }

  // #endregion RenderEvent

  // #region MovementEvent

  MovementEvent::MovementEvent(int x, int y)
  {
    this->x = x;
    this->y = y;
  }

  void MovementDispatcher::subscribe(MovementHandler *handler)
  {
    this->handlers.push_back(handler);

    handler->id = this->handlers.size();
  }

  void MovementDispatcher::unsubscribe(MovementHandler *handler)
  {
    auto it = this->handlers.begin() + handler->id;

    this->handlers.erase(it);
  }

  void MovementDispatcher::notify(MovementEvent *event)
  {
    for (auto handler : this->handlers)
    {
      handler->notify(event);
    }
  }

  // #endregion MovementEvent
}
