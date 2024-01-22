#ifndef IO_H
#define IO_H

#define IO_KEY_UP 119    // W
#define IO_KEY_DOWN 115  // S
#define IO_KEY_LEFT 97   // A
#define IO_KEY_RIGHT 100 // D
#define IO_KEY_ENTER 10  // Enter
#define IO_KEY_SPACE 32  // Space
#define IO_KEY_ESCAPE 27 // Esc

#include <fstream>
#include <vector>
#include <string>

namespace std
{
  vector<string> read_file(string path);

  /// @brief Handles keyboard input for game screens.
  class GameIO
  {
  };
}

#endif
