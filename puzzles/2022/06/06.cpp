// Puzzle is available at https://adventofcode.com/2022/day/6
// Keywords: set
#include "../2022.hpp"
#include "../../../src/utils.hpp"
#include <unordered_set>
using namespace std;

static std::string find_pos(const std::string &s, int num) {
  for (int i = num-1; i < s.size(); ++i) {
    unordered_set<char> tmp;
    for (int j = i-num+1; j <= i; ++j) {
      tmp.insert(s[j]);
    }
    if (tmp.size() == num) {
      return to_string(i+1);
    }
  }
  return ERROR_STRING;
}

std::string y2022::solve_06a(const std::vector<std::string> &input) {
  return find_pos(input[0], 4);
}

std::string y2022::solve_06b(const std::vector<std::string> &input) {
  return find_pos(input[0], 14);
}
