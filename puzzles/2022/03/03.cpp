// Puzzle is available at https://adventofcode.com/2022/day/3
// Keywords:
#include "../2022.hpp"
#include "../../../src/utils.hpp"
#include <unordered_set>
using namespace std;

static int calc_priority(char c) {
  if ('a' <= c && c <= 'z') {
    return c-'a'+1;
  }
  if ('A' <= c && c <= 'Z') {
    return c-'A'+27;
  }
  return 0;
}

std::string y2022::solve_03a(const std::vector<std::string> &input) {
  int count = 0;
  for (int i = 0; i < input.size(); ++i) {
    int size = input[i].size();
    unordered_set<char> s1;
    unordered_set<char> s2;
    for (int j = 0; j < size/2; ++j) {
      s1.insert(input[i][j]);
    }
    for (int j = size/2; j < size; ++j) {
      s2.insert(input[i][j]);
    }
    for (auto key: s1) {
      if (s2.contains(key)) {
        count += calc_priority(key);
      }
    }
  }
  return to_string(count);
}

std::string y2022::solve_03b(const std::vector<std::string> &input) {
  int count = 0;
  for (int i = 0; i < input.size(); ++i) {
    int size = input[i].size();
    unordered_set<char> s1;
    unordered_set<char> s2;
    unordered_set<char> s3;
    for (int j = 0; j < input[i].size(); ++j) {
      s1.insert(input[i][j]);
    }
    ++i;
    for (int j = 0; j < input[i].size(); ++j) {
      s2.insert(input[i][j]);
    }
    ++i;
    for (int j = 0; j < input[i].size(); ++j) {
      s3.insert(input[i][j]);
    }
    for (auto key: s1) {
      if (s2.contains(key) && s3.contains(key)) {
        count += calc_priority(key);
        break;
      }
    }
  }
  return to_string(count);
}
