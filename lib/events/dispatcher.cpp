#include <events/handler.h>
#include <events/dispatcher.h>

/// @brief Adds a new handler to the handlers list.
/// @param handler Pointer to a event handler.
template <typename E>
void EventDispatcher<E>::subscribe(IEventHandler<E> *handler)
{
  handler->id = this->handlers.size();

  this->handlers.push_back(handler);
}

/// @brief Removes a event handler.
/// @param handler Pointer to a event handler.
template <typename E>
void EventDispatcher<E>::unsubscribe(IEventHandler<E> *handler)
{
  auto id = handler->id;

  this->handlers.erase(this->handlers.begin() + id);
}

/// @brief Notifies all handlers of the event.
/// @param event A pointer to an event object.
template <typename E>
void EventDispatcher<E>::notify(E *event)
{
  for (auto handler : this->handlers)
  {
    handler->notify(event);
  }
}

// It isn't beautiful but it works ¯\_(ツ)_/¯
template class EventDispatcher<KeyboardEvent>;
template class EventDispatcher<MovementEvent>;
template class EventDispatcher<RenderEvent>;
template class EventDispatcher<GridStateEvent>;
