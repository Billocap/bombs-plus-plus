#include <iostream>
#include <string>

#include "lib/assert.h"

using namespace std;

int main()
{
  cout << "Hello, World!" << endl;

  string msg = "asdf";

  assert(false, msg);

  return 0;
}
