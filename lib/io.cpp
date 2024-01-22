#include "io.h"

namespace std
{
  // #region FileIO
  /// @brief Reads a basic text file.
  /// @param path File path.
  /// @return A vector containing all of the lines in the file.
  vector<string> read_file(string path)
  {
    ifstream file(path);
    vector<string> data;

    if (file.is_open())
    {
      string line;

      while (getline(file, line))
      {
        data.push_back(line);
      }

      file.close();
    }

    return data;
  }
  // #endregion FileIO
}
