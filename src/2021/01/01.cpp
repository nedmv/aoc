#include "../2021.hpp"
#include "../../utils.hpp"
using namespace std;

const std::string y2021::solve_01a(std::vector<std::string> input) {
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

const std::string y2021::solve_01b(std::vector<std::string> input) {
  size_t size = input.size();
  vector<int> data(size);
  transform(input.begin(), input.end(), data.begin(), stoiWrap);

  int count = 0;
  int sliding = 0;
  int sliding_old;

  for (size_t i = 1; i < size - 1; i++) {
    sliding_old = sliding;
    sliding = data[i-1] + data[i] + data[i + 1];
 
    if ((sliding > sliding_old)&& (i!= 1)) {
      count++;
    }
  }

  return to_string(count);
}
