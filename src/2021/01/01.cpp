// Puzzle is available at https://adventofcode.com/2020/day/1
#include "../2021.hpp"
#include "../../utils.hpp"
using namespace std;

std::string y2021::solve_01a(const std::vector<std::string> &input) {
  size_t size = input.size();
  vector<int> data(size);
  transform(input.begin(), input.end(), data.begin(), stoiWrap);

  int count = 0;

  for (size_t i = 1; i < size; i++) {
    if (data[i] > data[i - 1]) {
      count++;
    }
  }

  return to_string(count);
}

std::string y2021::solve_01b(const std::vector<std::string> &input) {
  size_t size = input.size();
  vector<int> data(size);
  transform(input.begin(), input.end(), data.begin(), stoiWrap);

  int count = 0;
  int sliding = 0;

  for (size_t i = 1; i < size - 1; i++) {
    int sliding_old = sliding;
    sliding = data[i-1] + data[i] + data[i + 1];
 
    if ((sliding > sliding_old)&& (i!= 1)) {
      count++;
    }
  }

  return to_string(count);
}
