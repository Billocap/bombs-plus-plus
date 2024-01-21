#include <iostream>
#include <string>

#include "lib/assert.h"
#include "lib/grid.h"

using namespace std;

int main()
{
  Grid g(4, 4);

  g.place_bombs(10);

  for (auto y = 0; y < g.height; y++)
  {
    for (auto x = 0; x < g.width; x++)
    {
      auto c = g.get_cell(x, y);

      if (c->has_bomb)
      {
        cout << "* ";
      }
      else
      {
        cout << c->bomb_count << " ";
      }
    }

    cout << endl;
  }

  return 0;
}
