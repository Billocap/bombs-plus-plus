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
  vector<string> read_file(string path);

  /// @brief Interface for classes that handle user input.
  class IInputHandler
  {
  public:
    /// @brief Method for handling keyboard input.
    /// @param key ASCII code for the key pressed.
    virtual void handle_input(int key) = 0;
  };
}

#endif
