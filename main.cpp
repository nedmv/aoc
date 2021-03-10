#include <algorithm>
#include <bitset>
#include <cstdlib>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

#include "Task.hpp"
#include "2020/2020.hpp"

using namespace std;
using namespace y2020;

int main() {
  Task t = Task();
  t.execute("01a", solve_01a);
  t.execute("01b", solve_01b);

  t.execute("02a", solve_02a);
  t.execute("02b", solve_02b);

  t.execute("03a", solve_03a);
  t.execute("03b", solve_03b);

  t.execute("04a", solve_04a);
  t.execute("04b", solve_04b);

  t.execute("05a", solve_05a);
  t.execute("05b", solve_05b);

  t.execute("06a", solve_06a);
  t.execute("06b", solve_06b);

  t.execute("07a", solve_07a);
  t.execute("07b", solve_07b);

  t.execute("08a", solve_08a);
  //t.execute("08b", solve_08b);
  return 0;
}