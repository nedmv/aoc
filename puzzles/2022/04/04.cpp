// Puzzle is available at https://adventofcode.com/2022/day/4
// Keywords:
#include "../../../src/utils.hpp"
#include "../2022.hpp"
using namespace std;

std::string y2022::solve_04a(const std::vector<std::string> &input) {
  regex reg(R"(([0-9]+)-([0-9]+),([0-9]+)-([0-9]+))");
  int count = 0;
  for (int i = 0; i < input.size(); ++i) {
    smatch match;
    regex_match(input[i], match, reg);
    int m1 = ToInt(match[1]);
    int m2 = ToInt(match[2]);
    int m3 = ToInt(match[3]);
    int m4 = ToInt(match[4]);
    if (((m1 <= m3) && (m2 >= m4)) || ((m3 <= m1) && (m4 >= m2))) {
      ++count;
    }
  }
  return to_string(count);
}

std::string y2022::solve_04b(const std::vector<std::string> &input) {
  regex reg(R"(([0-9]+)-([0-9]+),([0-9]+)-([0-9]+))");
  int count = 0;
  for (int i = 0; i < input.size(); ++i) {
    smatch match;
    regex_match(input[i], match, reg);
    int m1 = ToInt(match[1]);
    int m2 = ToInt(match[2]);
    int m3 = ToInt(match[3]);
    int m4 = ToInt(match[4]);
    if (((m1 >= m3) && (m1 <= m4)) || ((m2 >= m3) && (m2 <= m4)) ||
        ((m3 >= m1) && (m3 <= m2)) || ((m4 >= m1) && (m4 <= m2))) {
      ++count;
    }
  }
  return to_string(count);
}
