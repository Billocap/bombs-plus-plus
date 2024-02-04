#ifndef EVENTS_H
#define EVENTS_H

/// @brief Class for a single key press event.
class KeyboardEvent
{
public:
  /// @brief ASCII code of the key that was pressed.
  int key;

  KeyboardEvent(int key);
};

/// @brief Class for an event that triggers when the coordinates of an object changes.
class MovementEvent
{
public:
  /// @brief The new X coordinate.
  int x;
  /// @brief The new Y coordinate.
  int y;

  MovementEvent(int x, int y);
};

/// @brief Class for events that draws to the viewport.
class RenderEvent
{
public:
  /// @brief Width of the viewport.
  int width;
  /// @brief Height of the viewport.
  int height;
  /// @brief X coordinate to draw at.
  int x;
  /// @brief Y coordinate to draw at.
  int y;

  RenderEvent(int width, int height, int x, int y);
};

#endif
