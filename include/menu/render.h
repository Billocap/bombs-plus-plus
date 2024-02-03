#ifndef MENU_RENDER_H
#define MENU_RENDER_H

#include <ncursesw/ncurses.h>

#include "menu.h"

int render_option(std::MenuOption *option, std::RenderEvent *event);
void render_menu(std::Menu *menu, std::RenderEvent *event);

#endif
