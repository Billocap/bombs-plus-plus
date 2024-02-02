#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>

#include <events/events.h>
#include <events/kbd.h>
#include <events/render.h>

#include "ui.h"

namespace std
{
  class Menu;

  // #region Interfaces

  /// @brief Interface for a menu option object.
  class IMenuOption
  {
  public:
    /// @brief Defines the action this option performs.
    virtual void execute() = 0;
  };

  // #endregion Interfaces

  // #region Events

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

  // #endregion Events

  class Menu
  {
  public:
    MenuDrawer *drawer;
    MenuKeyboardHandler *on_key_press;
    MenuRenderHandler *on_render;

    Menu();

    void add_option(string label, IMenuOption *option);
    void pointer_up();
    void pointer_down();
    void execute();
    int get_pointer();

  private:
    int pointer = 0;
    vector<IMenuOption *> options;
  };
}

#endif
