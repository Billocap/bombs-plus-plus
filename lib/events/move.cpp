#include <events/move.h>

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
