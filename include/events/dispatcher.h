#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include <vector>

#include "handler.h"
#include "events.h"

/// @brief Class that can trigger events.
/// @tparam E The type of event this class dispatches.
template <typename E>
class EventDispatcher
{
protected:
  /// @brief List of subscribed handlers.
  std::vector<IEventHandler<E> *> handlers;

public:
  virtual void subscribe(IEventHandler<E> *handler);
  virtual void unsubscribe(IEventHandler<E> *handler);
  virtual void notify(E *event);
};

class GridStateEvent;

#endif
