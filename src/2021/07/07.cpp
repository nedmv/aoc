// Puzzle is available at https://adventofcode.com/2021/day/07
// Keywords: functional, lambda
#include <cmath>
#include <functional>

#include "../../utils.hpp"
#include "../2021.hpp"
using namespace std;

uint countMinFuelAmount(const std::string &data,
                        std::function<int(int)> costFunction) {
  vector<int> crabs = parseLineOfNumbers(data);
  const auto [min, max] = minmax_element(std::begin(crabs), std::end(crabs));

  vector<int> counters(*max - *min - 1, 0);

  for (int pos = *min + 1; pos < *max; ++pos) {
    for (auto crab : crabs) {
      counters[pos - *min - 1] += costFunction(abs(crab - pos));
    }
  }

  auto it = min_element(std::begin(counters), std::end(counters));

  return *it;
}

//use y = x as costFunction
const std::string y2021::solve_07a(std::vector<std::string> input) {
  return to_string(countMinFuelAmount(input[0], [](int x) { return x; }));
}

//use sum of arithmetic progression as costFunction
const std::string y2021::solve_07b(std::vector<std::string> input) {
  return to_string(
      countMinFuelAmount(input[0], [](int x) { return (x + 1) * x / 2; }));
}
