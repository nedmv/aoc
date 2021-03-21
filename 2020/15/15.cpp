#include "../2020.hpp"
using namespace std;

size_t countLastAge(vector<size_t> &nums) {
  auto it = find(nums.rbegin() + 1, nums.rend(), *nums.rbegin());
  if (it == nums.rend()) return 0;
  return it - nums.rbegin();
}

#if 0  // too slow for part b.
size_t solveUsingVector(vector<string> &input, size_t last_num) {
  string s;
  vector<size_t> nums;

  for (size_t i = 0; i < input.size(); i++) {
    s = input[i];
    size_t begin = 0;
    size_t end = s.find(",");
    while (true) {
      nums.push_back(stoi(s.substr(begin, end - begin)));
      if (end == s.npos) break;
      begin = end + 1;
      end = s.find(",", begin);
    }
  }
  for (size_t i = nums.size(); i < last_num; i++) {
    nums.push_back(countLastAge(nums));
  }
  return *(nums.end() - 1);
}
#endif

/**
 * @brief Much faster than first approach, through still takes ~40 seconds
 * for my PC to count part b.
 *
 */
size_t solveUsingMap(vector<string> &input, size_t last_num) {
  string s;
  map<size_t, size_t> data;  // 0 - num, 1 - last pos.
  size_t prev;
  size_t next;
  size_t pos = 0;

  for (size_t i = 0; i < input.size(); i++) {
    s = input[i];
    size_t begin = 0;
    size_t end = s.find(",");
    while (true) {
      prev = stoi(s.substr(begin, end - begin));
      if (end == s.npos) break;  // intentionally don't insert last number here
      data.insert_or_assign(prev, pos);
      pos++;
      begin = end + 1;
      end = s.find(",", begin);
    }
  }
  for (pos; pos < last_num - 1; pos++) {
    if (data.contains(prev)) {
      next = pos - data[prev];
    } else {
      next = 0;
    }
    data[prev] = pos;
    prev = next;
  }
  return prev;
}

const std::string y2020::solve_15a(std::vector<std::string> input) {
  return to_string(solveUsingMap(input, 2020));
}

const std::string y2020::solve_15b(std::vector<std::string> input) {
  return to_string(solveUsingMap(input, 30000000));
}
