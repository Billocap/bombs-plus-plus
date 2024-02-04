#ifndef MENU_EVENTS_H
#define MENU_EVENTS_H

#include <events/handler.h>
#include <events/events.h>

class Menu;

class MenuRenderHandler : public IEventHandler<RenderEvent>
{
public:
  MenuRenderHandler(Menu *menu);

  void notify(RenderEvent *event);

private:
  Menu *menu;
};

class MenuKeyboardHandler : public IEventHandler<KeyboardEvent>
{
public:
  MenuKeyboardHandler(Menu *menu);

  void notify(KeyboardEvent *event);

private:
  Menu *menu;
};

#endif
