#include <algorithm>
#include <bitset>
#include <cstdlib>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

#include "../puzzles/2020/2020.hpp"
#include "../puzzles/2021/2021.hpp"
#include "../puzzles/2022/2022.hpp"
#include "Task.hpp"
#include "utils.hpp"

using namespace std;

void year2021() {
  using namespace y2021;
  Task t;
  t.setYear(2021);

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
  t.execute("08b", solve_08b);

  t.execute("09a", solve_09a);
  t.execute("09b", solve_09b);

  t.execute("10a", solve_10a);
  t.execute("10b", solve_10b);

  t.execute("11a", solve_11a);
  t.execute("11b", solve_11b);

  t.execute("12a", solve_12a);
  t.execute("12b", solve_12b);

  t.execute("13a", solve_13a);
  t.execute("13b", solve_13b);

  t.execute("14a", solve_14a);
  t.execute("14b", solve_14b);

  t.execute("15a", solve_15a);
  t.execute("15b", solve_15b);

  t.execute("16a", solve_16a);
  t.execute("16b", solve_16b);

  t.execute("17a", solve_17a);
  t.execute("17b", solve_17b);

  t.execute("18a", solve_18a);
  t.execute("18b", solve_18b);

  // t.execute("19a", solve_19a);
  // t.execute("19b", solve_19b);

  t.execute("20a", solve_20a);
  t.execute("20b", solve_20b);

  t.execute("21a", solve_21a);
  t.execute("21b", solve_21b);

  // t.execute("22a", solve_22a);
  // t.execute("22b", solve_22b); 

  // t.execute("23a", solve_23a);
  // t.execute("23b", solve_23b);
}


void year2020() {
  using namespace y2020;
  Task t;
  t.setYear(2020);

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
  t.execute("08b", solve_08b);

  t.execute("09a", solve_09a);
  t.execute("09b", solve_09b);

  t.execute("10a", solve_10a);
  t.execute("10b", solve_10b);

  t.execute("11a", solve_11a);
  t.execute("11b", solve_11b);

  t.execute("12a", solve_12a);
  t.execute("12b", solve_12b);

  t.execute("13a", solve_13a);
  t.execute("13b", solve_13b);

  t.execute("14a", solve_14a);
  t.execute("14b", solve_14b);

  t.execute("15a", solve_15a);
  t.execute("15b", solve_15b);

  t.execute("16a", solve_16a);
}

void year2022() {
  using namespace y2022;
  Task t;
  t.setYear(2022);

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
  t.execute("08b", solve_08b);  

  t.execute("09a", solve_09a);
  t.execute("09b", solve_09b);

  t.execute("10a", solve_10a);
  t.execute("10b", solve_10b);

  t.execute("11a", solve_11a);
  t.execute("11b", solve_11b);

  t.execute("12a", solve_12a);
  t.execute("12b", solve_12b);

  t.execute("13a", solve_13a);
  t.execute("13b", solve_13b);
#if 0 //FIXME: optimization required
  t.execute("14a", solve_14a);
  t.execute("14b", solve_14b);

  t.execute("15a", solve_15a);
  t.execute("15b", solve_15b);

  t.execute("16a", solve_16a);
  t.execute("16b", solve_16b);

  t.execute("17a", solve_17a);
  t.execute("17b", solve_17b);

  t.execute("18a", solve_18a);
  t.execute("18b", solve_18b);

  t.execute("19a", solve_19a);
  t.execute("19b", solve_19b);

  t.execute("20a", solve_20a);
  t.execute("20b", solve_20b);

  t.execute("21a", solve_21a);
  t.execute("21b", solve_21b);
    
  t.execute("22a", solve_22a);
  t.execute("22b", solve_22b);

  t.execute("23a", solve_23a);
  t.execute("23b", solve_23b);
#endif

  t.execute("24a", solve_24a);
  t.execute("24b", solve_24b);

  t.execute("25a", solve_25a);
}

int main() {
  year2020();
  year2021();
  year2022();
  
}