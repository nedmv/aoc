#include "../2020.hpp"
using namespace std;

const std::string y2020::solve_09a(const std::vector<std::string> &input) {
  vector<uint64_t> data;
  size_t size = input.size();
  for (size_t i = 0; i < size; i++) {
    data.push_back(stoul(input[i]));
  }
  for (size_t i = 25; i < size; i++) {
    bool isValid = false;
    for (size_t j = i - 25; j < i - 1; j++) {
      for (size_t k = j + 1; k < i; k++) {
        if (data[i] == (data[j] + data[k])) {
          isValid = true;
          break;
        }
      }
      if (isValid) break;
    }
    if (!isValid) return to_string(data[i]);
  }

  return ERROR_STRING;
}

const std::string y2020::solve_09b(const std::vector<std::string> &input) {
  uint64_t target = stoul(solve_09a(input));
  size_t size = input.size();
  vector<uint64_t> data;
  for (size_t i = 0; i < size; i++) {
    data.push_back(stoul(input[i]));
  }
  uint64_t sum;
  for (size_t i = 0; i < size; i++) {
    if (data[i] >= target) continue;
    sum = 0;
    for (size_t j = i; j < size; j++) {
      if (sum < target) {
        sum += data[j];
      } else if (sum == target) {
        auto p = minmax_element(data.begin() + i, data.begin() + (j - 1));
        return to_string(*p.first + *p.second);
      } else {
        break;
      }
    }
  }
  return ERROR_STRING;
}