#include "menu.h"

namespace std
{
  // #region Menu

  Menu::Menu()
  {
    this->drawer = new MenuDrawer();
  }

  void Menu::add_option(string label, IMenuOption *option)
  {
    this->drawer->add_option(label);

    this->options.push_back(option);
  }

  void Menu::pointer_up()
  {
    this->pointer = (this->options.size() + this->pointer - 1) % this->options.size();

    this->drawer->focus(this->pointer);
  }

  void Menu::pointer_down()
  {
    this->pointer = (this->pointer + 1) % this->options.size();

    this->drawer->focus(this->pointer);
  }

  void Menu::execute()
  {
    this->options[this->pointer]->execute();
  }

  int Menu::get_pointer()
  {
    return this->pointer;
  }

  void Menu::handle_input(int key)
  {
    switch (key)
    {
    case IO_KEY_UP:
      this->pointer_up();
      break;

    case IO_KEY_DOWN:
      this->pointer_down();
      break;

    case IO_KEY_CONFIRM:
      this->execute();
      break;
    }
  }

  // #endregion Menu
}
