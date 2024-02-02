#include <ui/ui.h>

// #region TextBanner

TextBannerRenderHandler::TextBannerRenderHandler(TextBanner *banner)
{
  this->banner = banner;
}

void TextBannerRenderHandler::notify(std::RenderEvent *event)
{
  int _y = 0;

  init_pair(100, COLOR_YELLOW, COLOR_BLACK);

  attron(COLOR_PAIR(100) | A_DIM);

  for (auto line : this->banner->data)
  {
    if (_y >= event->height)
      break;

    mvprintw(event->y + _y, event->x - line.length() / 2, line.c_str());

    _y++;
  }

  attroff(COLOR_PAIR(100) | A_DIM);

  event->y += _y + 2;
}

/// @brief Creates a new text banner.
/// @param path Path to the file that contains the banner's data.
TextBanner::TextBanner(std::string path)
{
  this->on_render = new TextBannerRenderHandler(this);
  this->data = std::read_file(path);
}

// #endregion TextBanner
