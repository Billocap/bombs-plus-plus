#ifndef KEYBOARD_EVENT_H
#define KEYBOARD_EVENT_H

#include <vector>

#include "events.h"

class KeyboardEvent;

/// @brief Utility type for a keyboard handler.
typedef IEventHandler<KeyboardEvent> KeyboardHandler;

/// @brief Class for a single key press event.
class KeyboardEvent
{
public:
  /// @brief ASCII code of the key that was pressed.
  int key;

  KeyboardEvent(int key);
};

/// @brief Class that triggers key press events.
class KeyboardDispatcher : public IEventDispatcher<KeyboardEvent>
{
public:
  void subscribe(KeyboardHandler *handler);
  void unsubscribe(KeyboardHandler *handler);
  void notify(KeyboardEvent *event);
};

#endif