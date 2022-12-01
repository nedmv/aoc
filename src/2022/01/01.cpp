// Puzzle is available at https://adventofcode.com/2022/day/1
// Keywords:
#include "../2022.hpp"
#include "../../utils.hpp"
using namespace std;


vector<int> countCalories(const std::vector<std::string> &input) {
  vector<int> calories;
  int count = 0;
  for (size_t i = 0; i < input.size(); ++i) {
    if (!input[i].empty()) {
      count += stoi(input[i]);
    } else {
      calories.push_back(count);
      count = 0;
    }
  }
  calories.push_back(count);
  sort(calories.rbegin(), calories.rend());
  return calories;
}

std::string y2022::solve_01a(const std::vector<std::string> &input) {
  auto calories = countCalories(input);
  return to_string(calories[0]);
}

std::string y2022::solve_01b(const std::vector<std::string> &input) {
  auto calories = countCalories(input);
  return to_string(calories[0]+calories[1]+calories[2]);
}
