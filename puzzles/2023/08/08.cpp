// Puzzle is available at https://adventofcode.com/2023/day/8
// Keywords:
#include "../../../src/utils.hpp"
#include "../2023.hpp"
using namespace std;

struct Tree {
  string l;
  string r;
};

std::string y2023::solve_08a(const std::vector<std::string> &input) {
  long long ans = 0;
  const string path = input[0];

  unordered_map<string, Tree> m;
  for (int i = 3; i < input.size(); ++i) {
    if (input[i].empty()) {
      break;
    }
    string s = input[i];
    string name = s.substr(0, 3);
    Tree t;
    t.l = s.substr(7, 3);
    t.r = s.substr(12, 3);
    m[name] = t;
  }

  string name = "AAA";

  while (name != "ZZZ") {
    char c = path[ans % path.size()];
    auto cur = m[name];
    if (c == 'R') {
      name = cur.r;
    } else {
      name = cur.l;
    }
    ++ans;
  }

  return to_string(ans);
}

std::string y2023::solve_08b(const std::vector<std::string> &input) {
  long long ans = 0;
  const string path = input[0];

  unordered_map<string, Tree> m;
  for (int i = 2; i < input.size(); ++i) {
    if (input[i].empty()) {
      break;
    }
    string s = input[i];
    string name = s.substr(0, 3);
    Tree t;
    t.l = s.substr(7, 3);
    t.r = s.substr(12, 3);
    m[name] = t;
  }

  vector<string> state;
  for (const auto &[k, v] : m) {
    if (k[2] == 'A') {
      state.push_back(k);
    }
  }

  vector<long long> counts;

  for (auto &s : state) {
    long long count = 0;
    while (s[2] != 'Z') {
      char c = path[count % path.size()];
      auto cur = m[s];
      if (c == 'R') {
        s = cur.r;
      } else {
        s = cur.l;
      }
      ++count;
    }
    counts.push_back(count);
  }
  ans = 1;
  for (const auto &c : counts) {
    ans = lcm(ans, c);
  }

  return to_string(ans);
}
