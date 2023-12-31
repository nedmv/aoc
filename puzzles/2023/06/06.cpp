// Puzzle is available at https://adventofcode.com/2023/day/6
// Keywords:
#include "../../../src/utils.hpp"
#include "../2023.hpp"
using namespace std;

std::string y2023::solve_06a(const std::vector<std::string> &input) {
  long long ans = 1;
  auto time = ints(input[0]);
  auto distance = ints(input[1]);
  for (int t = 0; t < time.size(); ++t) {
    long long cur = 0;
    for (int i = 1; i < time[t]; ++i) {
      if ((time[t] - i) * i > distance[t]) {
        ++cur;
      }
    }
    ans *= cur;
  }
  return to_string(ans);
}

static long long parse_str(const string &s) {
  std::regex num(R"(([0-9]+))");
  auto begin = std::sregex_iterator(s.begin(), s.end(), num);
  auto end = std::sregex_iterator();
  string str;

  for (auto i = begin; i != end; ++i) {
    smatch match = *i;
    str += match[1].str();
  }
  return stoll(str);
}

std::string y2023::solve_06b(const std::vector<std::string> &input) {
  long long ans = 0;
  auto time = parse_str(input[0]);
  auto distance = parse_str(input[1]);
  for (long long i = 1; i < time; ++i) {
    if ((time - i) * i > distance) {
      ++ans;
    }
  }
  return to_string(ans);
}
