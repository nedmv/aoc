// Puzzle is available at https://adventofcode.com/2022/day/10
// Keywords:
#include "../2022.hpp"
#include "../../../src/utils.hpp"
#include <unordered_set>
using namespace std;

std::string y2022::solve_10a(const std::vector<std::string> &input) {
  int cycle = 1;
  int count = 0;
  int x = 1;
  unordered_set<int> values = {20, 60, 100, 140, 180, 220};
  for (int i = 0; i < input.size(); ++i) {
    if (input[i].starts_with("addx")) {
      cycle += 1;
      if (values.contains(cycle) ) {
        count += cycle * x;
      }
      cycle += 1;
      x += stoi(input[i].substr(5));
      if (values.contains(cycle) ) {
        count += cycle * x;
      }
    } else {
      ++cycle;
      if (values.contains(cycle)) {
      count += cycle * x;
      }
    }
  }
  return to_string(count);
}

static char next_char(int cycle, int x) {
  return (cycle%40 >= x-1 && cycle%40 <= x+1) ? '#' : '.';
}

std::string y2022::solve_10b(const std::vector<std::string> &input) {
  int cycle = 0;
  int x = 1;
  string result;
  for (int i = 0; i < input.size(); ++i) {
    if (input[i].starts_with("addx")) {
      result.push_back(next_char(cycle, x));
      ++cycle;
      result.push_back(next_char(cycle, x));
      ++cycle;
      x += stoi(input[i].substr(5));
    } else {
      result.push_back(next_char(cycle, x));
      ++cycle;
    }
  }
  for (int i = 0; i < 6; ++i) {
    cout << result.substr(40*i, 40) << "\n";
  }
  cout << "\n";
  return result;
}
