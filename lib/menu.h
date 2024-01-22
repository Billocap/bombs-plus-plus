#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>

#include "io.h"
#include "ui.h"

namespace std
{
  class IMenuOption
  {
  public:
    virtual void execute() = 0;
  };

  class Menu
  {
  public:
    MenuDrawer *drawer;

    Menu();

    void add_option(string label, IMenuOption *option);
    void pointer_up();
    void pointer_down();
    void execute();
    int get_pointer();
    void handle_input(int key);

  private:
    int pointer = 0;
    vector<IMenuOption *> options;
  };
}

#endif