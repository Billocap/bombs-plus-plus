#ifndef GAME_H
#define GAME_H

namespace std
{
  class Game
  {
  public:
    bool is_running();
    void start();
    void stop();

  private:
    /// @brief Defines if the game is running or not.
    bool running = true;
  };
}

#endif
