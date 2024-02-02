#ifndef EVENTS_H
#define EVENTS_H

#include <vector>

namespace std
{
  /// @brief Interface for a class that handles events.
  /// @tparam E The type of event this class handles.
  template <typename E>
  class IEventHandler
  {
  public:
    /// @brief The id is the position of this handler in the handlers list.
    int id;

    /// @brief Triggers an action when the event happens.
    /// @param event Object that describes the event.
    virtual void notify(E *event) = 0;
  };

  /// @brief Interface for a class that can trigger events.
  /// @tparam E The type of event this class dispatches.
  /// @tparam H The type of event handler this class accepts.
  template <typename E, typename H = IEventHandler<E>>
  class IEventDispatcher
  {
  protected:
    /// @brief List of subscribed handlers.
    vector<H *> handlers;

  public:
    /// @brief Adds a new handler to the handlers list.
    /// @param handler Pointer to a event handler.
    virtual void subscribe(H *handler) = 0;
    /// @brief Removes a event handler.
    /// @param handler Pointer to a event handler.
    virtual void unsubscribe(H *handler) = 0;
    /// @brief Notifies all handlers of the event.
    /// @param event A pointer to an event object.
    virtual void notify(E *event) = 0;
  };
}

#endif
