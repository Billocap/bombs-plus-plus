#include <menu/opts.h>
#include <menu/events.h>
#include <menu/menu.h>

namespace std
{
  // #region Events
  //  #region MenuRenderHandler

  MenuRenderHandler::MenuRenderHandler(Menu *menu)
  {
    this->menu = menu;
  }

  void MenuRenderHandler::notify(RenderEvent *event)
  {
    this->menu->drawer->resize_clip_box(event->width, event->height);
    this->menu->drawer->draw(event->y, event->x);
  }

  // #endregion MenuRenderHandler

  //  #region MenuKeyboardHandler

  MenuKeyboardHandler::MenuKeyboardHandler(Menu *menu)
  {
    this->menu = menu;
  }

  void MenuKeyboardHandler::notify(KeyboardEvent *event)
  {
    switch (event->key)
    {
    case IO_KEY_UP:
      this->menu->pointer_up();
      break;

    case IO_KEY_DOWN:
      this->menu->pointer_down();
      break;

    case IO_KEY_CONFIRM:
      this->menu->execute();
      break;
    }
  }

  // #endregion MenuKeyboardHandler
  // #endregion Events

  // #region Menu

  Menu::Menu()
  {
    this->drawer = new MenuDrawer();
    this->on_key_press = new MenuKeyboardHandler(this);
    this->on_render = new MenuRenderHandler(this);
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

  // #endregion Menu
}
