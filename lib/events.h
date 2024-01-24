#ifndef EVENTS_H
#define EVENTS_H

#include <vector>

namespace std
{
  // #region Interfaces

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

  // #endregion Interfaces

  // #region KeyboardEvent

  class KeyboardEvent
  {
  public:
    int key;

    KeyboardEvent(int key);
  };

  typedef IEventHandler<KeyboardEvent> KeyboardHandler;

  class KeyboardDispatcher : public IEventDispatcher<KeyboardEvent>
  {
  public:
    void subscribe(KeyboardHandler *handler);
    void unsubscribe(KeyboardHandler *handler);
    void notify(KeyboardEvent *event);

  private:
    vector<KeyboardHandler *> handlers;
  };

  // #endregion KeyboardEvent

  // #region RenderEvent

  class RenderEvent
  {
  public:
    int width;
    int height;
    int x;
    int y;

    RenderEvent(int width, int height, int x, int y);
  };

  typedef IEventHandler<RenderEvent> RenderHandler;

  class RenderDispatcher : public IEventDispatcher<RenderEvent>
  {
  public:
    void subscribe(RenderHandler *handler);
    void unsubscribe(RenderHandler *handler);
    void notify(RenderEvent *event);

  private:
    vector<RenderHandler *> handlers;
  };

  // #endregion RenderEvent

  // #region MovementEvent

  class MovementEvent
  {
  public:
    int x;
    int y;

    MovementEvent(int x, int y);
  };

  typedef IEventHandler<MovementEvent> MovementHandler;

  class MovementDispatcher : public IEventDispatcher<MovementEvent>
  {
  public:
    void subscribe(MovementHandler *handler);
    void unsubscribe(MovementHandler *handler);
    void notify(MovementEvent *event);

  private:
    vector<MovementHandler *> handlers;
  };

  // #endregion MovementEvent
}

#endif
