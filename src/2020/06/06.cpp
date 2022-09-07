// Puzzle is available at https://adventofcode.com/2020/day/6
// Keywords: bitset
#include "../2020.hpp"
using namespace std;

const std::string y2020::solve_06a(const std::vector<std::string> &input) {
  bitset<26> b;
  size_t result = 0;
  uint8_t id;
  for (size_t i = 0; i < input.size(); i++) {
    size_t size = input[i].size();
    if (size == 0) {
      result += b.count();
      b.reset();
    } else {
      for (size_t j = 0; j < size; j++) {
        id = input[i].at(j) - 'a';
        b[id] = true;
      }
    }
  }
  result += b.count();
  return to_string(result);
}

const std::string y2020::solve_06b(const std::vector<std::string> &input) {
  bitset<26> common_answers, current_answers;
  common_answers.set();
  size_t result = 0;
  uint8_t id;
  for (size_t i = 0; i < input.size(); i++) {
    size_t size = input[i].size();
    if (size == 0) {
      result += common_answers.count();
      common_answers.set();
    } else {
      for (size_t j = 0; j < size; j++) {
        id = input[i].at(j) - 'a';
        current_answers[id] = true;
      }
      common_answers = common_answers & current_answers;
      current_answers.reset();
    }
  }
  result += common_answers.count();
  return to_string(result);
}