#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include <vector>

#include "handler.h"

/// @brief Class that can trigger events.
/// @tparam E The type of event this class dispatches.
template <typename E>
class EventDispatcher
{
protected:
  /// @brief List of subscribed handlers.
  std::vector<IEventHandler<E> *> handlers;

public:
  /// @brief Adds a new handler to the handlers list.
  /// @param handler Pointer to a event handler.
  void subscribe(IEventHandler<E> *handler)
  {
    handler->id = this->handlers.size();

    this->handlers.push_back(handler);
  };

  /// @brief Removes a event handler.
  /// @param handler Pointer to a event handler.
  void unsubscribe(IEventHandler<E> *handler)
  {
    auto id = handler->id;

    this->handlers.erase(this->handlers.begin() + id);
  };

  /// @brief Notifies all handlers of the event.
  /// @param event A pointer to an event object.
  void notify(E *event)
  {
    for (auto handler : this->handlers)
      handler->notify(event);

    delete event;
  };
};

#endif
