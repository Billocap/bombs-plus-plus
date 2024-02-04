#include <io.h>

/// @brief Reads a basic text file.
/// @param path File path.
/// @return A vector containing all of the lines in the file.
std::vector<std::string> read_file(std::string path)
{
  std::ifstream file(path);
  std::vector<std::string> data;

  if (file.is_open())
  {
    std::string line;

    while (getline(file, line))
    {
      data.push_back(line);
    }

    file.close();
  }

  return data;
}

std::string read_save(std::string path)
{
  std::ifstream file(path);
  std::string data;

  if (file.is_open())
  {
    std::string line;

    while (getline(file, line))
    {
      data += line;
    }

    file.close();
  }

  return data;
};

void write_save(std::string path, std::string data)
{
  std::ofstream file(path);

  if (file.is_open())
  {
    file << data;

    file.close();
  }
}

void delete_save(std::string path)
{
  remove(path.c_str());
}
