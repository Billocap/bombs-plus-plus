#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>

#include <ui/ui.h>

#include "events.h"

namespace std
{
  /// @brief Interface for a class that executes actions.
  class IMenuAction
  {
  public:
    /// @brief Defines the action this option performs.
    virtual void execute() = 0;
  };

  /// @brief Smallest part of a menu.
  class MenuOption
  {
  private:
    /// @brief Object that performs an action.
    IMenuAction *action;

  public:
    /// @brief Label to be displayed.
    string label;
    /// @brief If this option is in focus.
    bool focused = false;

    MenuOption(string label, IMenuAction *action);

    void execute();
  };

  class Menu
  {
  private:
    int pointer = 0;

  public:
    TextBanner *banner;
    MenuKeyboardHandler *on_key_press;
    MenuRenderHandler *on_render;
    vector<MenuOption *> options;

    Menu(TextBanner *banner);

    void add_option(string label, IMenuAction *action);
    void pointer_up();
    void pointer_down();
    void execute();
    int get_pointer();
  };
}

#endif
