// Puzzle is available at https://adventofcode.com/2021/day/18
// Keywords:
#include "../2021.hpp"
#include "../../utils.hpp"
#include <memory>
#include <algorithm>

using namespace std;

struct RegularNumber {
  RegularNumber(int value, int level): value{value}, level{level} {}
  ~RegularNumber() {}
  int value;
  int level;
};

static vector<RegularNumber> parseSnailfishNumber(const string &str) {
  vector<RegularNumber> result;
  int openedBraces = 0;

  for (size_t i = 0; i < str.size(); i++) {
    if (('0' <= str[i]) && (str[i] <= '9')) {
      result.push_back(RegularNumber(str[i] - '0', openedBraces));
    } else if (str[i] == '[') {
        openedBraces++;
    } else if (str[i] == ']') {
      openedBraces--;
    }
  }
  return result;
}

static bool explode(vector<RegularNumber> &num) {
  bool exploded = false;
  for (auto it = num.begin(); it != num.end(); ++it) {
    if (it->level == 5) {
      if (it != num.begin()) {
        (it-1)->value += it->value;
      }
      if ((it + 2) != num.end()) {
        (it+2)->value += (it+1)->value;
      }
      *it = RegularNumber(0, 4);
      num.erase(it+1);
      exploded = true;
      break;
    }
  }
  return exploded;
}

static bool split(vector<RegularNumber> &num) {
  bool splitted = false;
  for (auto it = num.begin(); it != num.end(); ++it) {
    if (it->value >= 10) {
      int value = it->value;
      it->value = value/2;
      it->level++;
      num.insert(it+1, RegularNumber(it->value + value%2, it->level));
      splitted = true;
      break;
    }
  }
  return splitted;
}

static void reduce(vector<RegularNumber> &num) {
  while(true) {
    if (explode(num) || split(num)) {
      continue;
    } else {
      break;
    }
  }
}

static vector<RegularNumber> sum(const vector<RegularNumber> &num1, const vector<RegularNumber> &num2) {
  vector result = num1;
  copy(num2.begin(), num2.end(), back_inserter(result));
  for (int i = 0; i < result.size(); i++) {
    result[i].level++;
  }
  reduce(result);
  return result;
}

static size_t countMagnitude(vector<RegularNumber> num) {
  for (int level = 4; level > 0; level--) {
    auto hasLevel = [level](RegularNumber reg) {
      return reg.level == level;
    };
    while (true) {
      auto it = find_if(num.begin(), num.end(), hasLevel);
      if (it != num.end()) {
        it->level--;
        it->value = it->value * 3 + (it+1)->value * 2;
        num.erase(it+1);
      } else {
        break;
      }
    }
  }
  return num[0].value;
}

std::string y2021::solve_18a(const std::vector<std::string> &input) {
  auto result = parseSnailfishNumber(input[0]);
  for (int i = 1; i < input.size(); i++) {
    auto current = parseSnailfishNumber(input[i]);
    result = sum(result, current);
  }
  return to_string(countMagnitude(result));
}

std::string y2021::solve_18b(const std::vector<std::string> &input) {
  size_t size = input.size();
  size_t maxMagnitude = 0;
  vector<vector<RegularNumber>> nums;
  for (int i = 0; i < size; i++) {
    nums.push_back(parseSnailfishNumber(input[i]));
  }
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (i != j) {
        size_t magnitude = countMagnitude(sum(nums[i], nums[j]));
        if (magnitude > maxMagnitude) {
          maxMagnitude = magnitude;
        }
      }
    }
  }
  return to_string(maxMagnitude);
}