#include <io.h>

namespace std
{
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

  string read_save(string path)
  {
    ifstream file(path);
    string data;

    if (file.is_open())
    {
      string line;

      while (getline(file, line))
      {
        data += line;
      }

      file.close();
    }

    return data;
  };

  void write_save(string path, string data)
  {
    ofstream file(path);

    if (file.is_open())
    {
      file << data;

      file.close();
    }
  }

  void delete_save(string path)
  {
    remove(path.c_str());
  }
}
