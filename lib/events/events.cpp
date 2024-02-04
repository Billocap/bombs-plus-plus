#include <events/events.h>

KeyboardEvent::KeyboardEvent(int key)
{
  this->key = key;
}

MovementEvent::MovementEvent(int x, int y)
{
  this->x = x;
  this->y = y;
}

RenderEvent::RenderEvent(int width, int height, int x, int y)
{
  this->width = width;
  this->height = height;
  this->x = x;
  this->y = y;
}
