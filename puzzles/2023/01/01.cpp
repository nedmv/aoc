// Puzzle is available at https://adventofcode.com/2023/day/1
// Keywords:
#include "../../../src/utils.hpp"
#include "../2023.hpp"
using namespace std;

std::string y2023::solve_01a(const std::vector<std::string> &input) {
  int sum = 0;

  for (int i = 0; i < input.size(); ++i) {
    for (int j = 0; j < input[i].size(); ++j) {
      char c = input[i][j];
      if (isdigit(c)) {
        sum += (c - '0') * 10;
        break;
      }
    }
    for (int j = input[i].size() - 1; j >= 0; --j) {
      char c = input[i][j];
      if (isdigit(c)) {
        sum += (c - '0');
        break;
      }
    }
  }
  return to_string(sum);
}

std::string y2023::solve_01b(const std::vector<std::string> &input) {
  vector<string> digits = {"one", "two", "three", "four", "five",
                           "six", "seven", "eight", "nine"};
  int sum = 0;
  for (int i = 0; i < input.size(); ++i) {
    int min_pos = input[i].size();
    int min_digit = 0;
    for (int d = 0; d < 9; ++d) {
      int pos = input[i].find(digits[d]);
      if (pos != string::npos && min_pos > pos) {
        min_pos = pos;
        min_digit = d + 1;
      }
    }
    for (int j = 0; j < min_pos; ++j) {
      if (isdigit(input[i][j])) {
        min_digit = input[i][j] - '0';
        break;
      }
    }

    int max_pos = 0;
    int max_digit = 0;
    for (int d = 0; d < 9; ++d) {
      int pos = input[i].rfind(digits[d]);
      if (pos != string::npos && max_pos < pos) {
        max_pos = pos;
        max_digit = d + 1;
      }
    }
    for (int j = input[i].size() - 1; j >= max_pos; --j) {
      if (isdigit(input[i][j])) {
        max_digit = input[i][j] - '0';
        break;
      }
    }
    int code = min_digit * 10 + max_digit;
    sum += code;
  }
  return to_string(sum);
}
