// Puzzle is available at https://adventofcode.com/2022/day/25
// Keywords:
#include "../../../src/utils.hpp"
#include "../2022.hpp"
using namespace std;

long long to_dec(const string &s) {
  long long mul = 1;
  long long result = 0;
  for (int i = s.size() - 1; i >= 0; i--) {
    long long cur = 0;
    switch (s[i]) {
      case '2':
        cur += 2;
        break;
      case '1':
        cur += 1;
        break;
      case '-':
        cur -= 1;
        break;
      case '=':
        cur -= 2;
        break;
    }
    result += cur * mul;
    mul *= 5;
  }
  return result;
}

bool in_range(long long num, long long mul) {
  if (mul <= 1) {
    return (num <= 2) && (num >= -2);
  }
  if (num / mul < 2 && num / mul > -2) {
    return true;
  }
  if (num / mul == 2 && in_range(num - 2 * mul, mul / 5)) {
    return true;
  }
  if (num / mul == -2 && in_range(num + 2 * mul, mul / 5)) {
    return true;
  }
  return false;
}

string to_snafu(long long num) {
  long long mul = 1;
  while (num > 2 * mul) {
    mul *= 5;
  }
  string result;
  while (mul > 1) {
    for (int i = -2; i <= 2; ++i) {
      if (in_range(num - mul * i, mul / 5)) {
        switch (i) {
          case 2:
            result.push_back('2');
            break;
          case 1:
            result.push_back('1');
            break;
          case 0:
            result.push_back('0');
            break;
          case -1:
            result.push_back('-');
            break;
          case -2:
            result.push_back('=');
            break;
        }
        num -= (i * mul);
        mul /= 5;
        break;
      }
    }
    switch (num) {
      case 2:
        result.push_back('2');
        break;
      case 1:
        result.push_back('1');
        break;
      case 0:
        result.push_back('0');
        break;
      case -1:
        result.push_back('-');
        break;
      case -2:
        result.push_back('=');
        break;
    }
  }
  return result;
}

std::string y2022::solve_25a(const std::vector<std::string> &input) {
  vector<string> snafu;
  for (int i = 0; i < input.size(); ++i) {
    if (input[i].empty()) {
      break;
    }
    snafu.push_back(input[i]);
  }

  long long sum = 0;
  for (const auto &s : snafu) {
    sum += to_dec(s);
  }
  return to_snafu(sum);
}
