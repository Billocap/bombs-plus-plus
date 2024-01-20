#ifndef ASSERT_H
#define ASSERT_H

#include <string>

namespace std
{
  void assert(bool condition);
  void assert(bool condition, const char msg[]);
  void assert(bool condition, string msg);
}

#endif
