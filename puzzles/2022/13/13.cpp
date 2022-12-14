// Puzzle is available at https://adventofcode.com/2022/day/13
// Keywords: nested lists
#include "../../../src/utils.hpp"
#include "../2022.hpp"
using namespace std;

int compare_nums(int left, int right) {
  if (left == right) return 0;
  return (left < right) ? 1 : -1;
}

bool isNum(const string &s) {
  for (int i = 0; i < s.size(); i++) {
    if (s[i] >= '0' && s[i] <= '9') {
      continue;
    } else {
      return false;
    }
  }
  return true;
}

vector<string> tokenize(const string &s) {
  vector<string> tokens;
  if (s.empty()) {
    tokens.push_back("");
    return tokens;
  }
  if (isNum(s)) {
    tokens.push_back(s);
    return tokens;
  }

  int start = 1;
  int brackets = 0;
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == '[') {
      ++brackets;
    } else if (s[i] == ']') {
      --brackets;
      if (brackets == 0) {
        tokens.push_back(s.substr(start, i - start));
      }
    } else if (s[i] == ',') {
      if (brackets == 1) {
        tokens.push_back(s.substr(start, i - start));
        start = i + 1;
      }
    }
  }
  return tokens;
}

int compare(const vector<string> &left, const vector<string> &right) {
  int result = 0;
  for (int i = 0; i < left.size() && i < right.size(); i++) {
    if (left[i].empty() || right[i].empty()) {
      if (!left[i].empty() || !right[i].empty()) {
        result = (left[i].empty()) ? 1 : -1;
      }
    } else if (isNum(left[i]) && isNum(right[i])) {
      result = compare_nums(stoi(left[i]), stoi(right[i]));
    } else {
      result = compare(tokenize(left[i]), tokenize(right[i]));
    }
    if (result != 0) {
      return result;
    }
  }
  if (left.size() == right.size()) {
    return 0;
  }
  return (left.size() < right.size()) ? 1 : -1;
}

std::string y2022::solve_13a(const std::vector<std::string> &input) {
  int index = 1;
  int sum = 0;
  for (int i = 0; i < input.size(); i += 3) {
    if (compare(tokenize(input[i]), tokenize(input[i + 1])) >= 0) {
      sum += index;
    }
    ++index;
  }
  return to_string(sum);
}

std::string y2022::solve_13b(const std::vector<std::string> &input) {
  int a = 1;
  int b = 1;
  for (int i = 0; i < input.size(); ++i) {
    if (!input[i].empty()) {
      if (compare(tokenize(input[i]), tokenize("[[2]]")) >= 0) {
        ++a;
      } else if (compare(tokenize(input[i]), tokenize("[[6]]")) >= 0) {
        ++b;
      }
    }
  }
  return to_string(a * (a + b));
}
