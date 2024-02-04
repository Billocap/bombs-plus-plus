#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

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

#endif
