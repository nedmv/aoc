// Puzzle is available at https://adventofcode.com/2020/day/1
// Keywords: std::transform
#include "../2020.hpp"
#include "../../utils.hpp"
using namespace std;

const std::string y2020::solve_01a(std::vector<std::string> input) {
  size_t size = input.size();
  vector<int> data(size);
  transform(input.begin(), input.end(), data.begin(), stoiWrap);

  for (size_t i = 0; i < size; i++) {
    for (size_t j = i + 1; j < size; j++) {
      if ((data[i] + data[j]) == 2020) return to_string(data[i] * data[j]);
    }
  }
  return ERROR_STRING;
}

const std::string y2020::solve_01b(std::vector<std::string> input) {
  size_t size = input.size();
  vector<int> data(size);
  transform(input.begin(), input.end(), data.begin(), stoiWrap);

  for (size_t i = 0; i < size; i++) {
    for (size_t j = i + 1; j < size; j++) {
      for (size_t k = j + 1; k < size; k++) {  // stick to the plan!
        if ((data[i] + data[j] + data[k]) == 2020) {
          return to_string(data[i] * data[j] * data[k]);
        }
      }
    }
  }
  return ERROR_STRING;
}