#ifndef MENU_RENDER_H
#define MENU_RENDER_H

#include <ncursesw/ncurses.h>

#include "menu.h"

int render_option(MenuOption *option, RenderEvent *event);
void render_menu(Menu *menu, RenderEvent *event);

#endif
