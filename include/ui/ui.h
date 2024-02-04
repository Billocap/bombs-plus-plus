#ifndef UI_H
#define UI_H

#include <vector>
#include <string>
#include <ncursesw/ncurses.h>

#include <events/events.h>
#include <io.h>

// #region Banner

class TextBanner;

class TextBannerRenderHandler
{
public:
  TextBannerRenderHandler(TextBanner *banner);

  void notify(RenderEvent *event);

private:
  TextBanner *banner;
};

/// @brief Text banner are used to improve the UI.
class TextBanner
{
public:
  /// @brief Actual data contained in the banner file.
  std::vector<std::string> data;
  TextBannerRenderHandler *on_render;

  TextBanner(std::string file);
};

// #endregion Banner

#endif
