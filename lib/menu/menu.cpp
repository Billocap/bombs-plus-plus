#include <menu/opts.h>
#include <menu/events.h>
#include <menu/menu.h>
#include <menu/render.h>

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
    this->menu->banner->on_render->notify(event);

    render_menu(this->menu, event);
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

  // #region MenuOption

  /// @brief Creates a new menu option.
  /// @param label Label for the option.
  /// @param action Action handler for the option.
  MenuOption::MenuOption(string label, IMenuAction *action)
  {
    this->label = label;
    this->action = action;
  }

  /// @brief Runs the action handler.
  void MenuOption::execute()
  {
    this->action->execute();
  }

  // #endregion MenuOption

  // #region Menu

  Menu::Menu(TextBanner *banner)
  {
    this->on_key_press = new MenuKeyboardHandler(this);
    this->on_render = new MenuRenderHandler(this);
    this->banner = banner;
  }

  void Menu::add_option(string label, IMenuAction *action)
  {
    this->options.push_back(new MenuOption(label, action));
  }

  void Menu::remove_option(int id)
  {
    auto it = this->options.begin() + id;

    this->options.erase(it);
  }

  void Menu::pointer_up()
  {
    this->options[this->pointer]->focused = false;

    this->pointer = (this->options.size() + this->pointer - 1) % this->options.size();

    this->options[this->pointer]->focused = true;
  }

  void Menu::pointer_down()
  {
    this->options[this->pointer]->focused = false;

    this->pointer = (this->pointer + 1) % this->options.size();

    this->options[this->pointer]->focused = true;
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

int render_option(std::MenuOption *option, std::RenderEvent *event)
{
  auto label = option->label;

  if (option->focused)
  {
    label = "[" + label + "]";
  }

  mvprintw(event->y, event->x - label.length() / 2, label.c_str());

  return event->y + 1;
}

void render_menu(std::Menu *menu, std::RenderEvent *event)
{
  init_pair(1, COLOR_WHITE, COLOR_BLACK);

  attron(COLOR_PAIR(1));

  int y = event->y;

  for (auto option : menu->options)
  {
    if (y >= event->height)
      break;

    auto child_event = new std::RenderEvent(event->width, event->height, event->x, y);

    y = render_option(option, child_event);
  }

  y += 2;

  if (y < event->height)
  {
    std::string line = "Created by Gabriel Quintino";

    init_pair(2, COLOR_BLUE, COLOR_BLACK);

    mvprintw(y, event->x - line.length() / 2, "Created by ");
    attron(COLOR_PAIR(2));
    printw("Gabriel Quintino");
    attron(COLOR_PAIR(1));
  }
}
