#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>

#include "events.h"

#include "../../lib/ui.h"

namespace std
{
  /// @brief Interface for a menu option object.
  class IMenuOption
  {
  public:
    /// @brief Defines the action this option performs.
    virtual void execute() = 0;
  };

  class Menu
  {
  private:
    int pointer = 0;
    vector<IMenuOption *> options;

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
  };
}

#endif
