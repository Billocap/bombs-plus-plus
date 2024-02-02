#ifndef IO_H
#define IO_H

#define IO_KEY_UP 119     // W
#define IO_KEY_DOWN 115   // S
#define IO_KEY_LEFT 97    // A
#define IO_KEY_RIGHT 100  // D
#define IO_KEY_CONFIRM 10 // Enter
#define IO_KEY_ACCENT 32  // Space
#define IO_KEY_MENU 27    // Esc

#include <fstream>
#include <vector>
#include <string>

namespace std
{
  // #region FileIO

  vector<string> read_file(string path);

  // #endregion FileIO
}

#endif
