#include <events/render.h>

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
