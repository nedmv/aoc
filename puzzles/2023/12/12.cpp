// Puzzle is available at https://adventofcode.com/2023/day/12
// Keywords:
#include "../2023.hpp"
#include "../../../src/utils.hpp"
using namespace std;

long long correct_arrangements(vector<long long> &order, string &s, int pos, int id, map<int, map<int, long long>> &dp) {
  if (pos >= s.size() && id == order.size()) {
    return 1;
  }
  if (id < order.size() && pos + order[id] > s.size()) {
    return 0;
  }
  if (id == order.size() && s[pos] == '#') {
    return 0;
  }
  if (dp.contains(id) && dp[id].contains(pos)) {
    return dp[id][pos];
  }

  long long res = 0;

  if (s[pos] != '#') {
    res += correct_arrangements(order, s, pos+1, id, dp);
  }
  
  if (id < order.size()) {
    long long i;
    for (i = 0; i < order[id]; ++i) {
      if (s[i + pos] == '.') {
        break;
      }
    }
    if (i == order[id]) {
      if (s[pos + order[id]] == '#') {
        res += 0;
      } else {
        res += correct_arrangements(order, s, pos+order[id]+1, id+1, dp);
      }
    }
  }
  return dp[id][pos] = res;
}

std::string y2023::solve_12a(const std::vector<std::string> &input) {
  long long ans = 0;

  for (const auto &line: input) {
    if (line.empty()) {
      break;
    }
    auto order = ints(line);
    auto s = line.substr(0, line.find(' '));
    map<int, map<int, long long>> dp;
    long long a = correct_arrangements(order, s, 0, 0, dp);
    ans += a;
  }
  return to_string(ans);
}

std::string y2023::solve_12b(const std::vector<std::string> &input) {
  long long ans = 0;

  for (const auto &line: input) {
    if (line.empty()) {
      break;
    }
    auto order = ints(line);
    auto copy = ints(line);

    auto s = line.substr(0, line.find(' '));
    auto li = s;
    for (int i = 0; i < 4; ++i) {
      for (const auto &n: copy) {
        order.push_back(n);
      }
      s += '?' + li;
    }
    map<int, map<int, long long>> dp;
    long long a = correct_arrangements(order, s, 0, 0, dp);
    ans += a;
  }

  return to_string(ans);
}
