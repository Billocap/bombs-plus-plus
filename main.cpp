#include <iostream>
#include <string>

#include "lib/assert.h"
#include "lib/grid.h"

using namespace std;

int main()
{
  Grid g(4, 4);

  // g.place_bomb(1, 1);

  for (auto y = 0; y < g.height; y++)
  {
    for (auto x = 0; x < g.width; x++)
    {
      auto c = g.get_cell(x, y);

      cout << c->bomb_count << " ";
    }

    cout << endl;
  }

  return 0;
}
