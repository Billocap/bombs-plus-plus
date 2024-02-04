#include <events/kbd.h>

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
