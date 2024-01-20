#include "assert.h"

namespace std
{
  /// @brief Throws an error when the `condition` is `false`.
  /// @param condition The condition to be verified.
  void assert(bool condition)
  {
    if (!condition)
      throw "❌ Assestion error: the condition was false.";
  }

  /// @brief Throws `msg` when the `condition` is `false`.
  /// @param condition The condition to be verified.
  /// @param msg Error message to be thrown.
  void assert(bool condition, const char msg[])
  {
    if (!condition)
      throw msg;
  }

  /// @brief Throws `msg` when the `condition` is `false`.
  /// @param condition The condition to be verified.
  /// @param msg Error message to be thrown.
  void assert(bool condition, string msg)
  {
    if (!condition)
      throw msg;
  }
}
