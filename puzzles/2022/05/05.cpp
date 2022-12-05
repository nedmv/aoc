// Puzzle is available at https://adventofcode.com/2022/day/5
// Keywords: stack, regex
#include <stack>

#include "../../../src/utils.hpp"
#include "../2022.hpp"
using namespace std;

std::string y2022::solve_05a(const std::vector<std::string> &input) {
  vector<stack<char>> stacks(10);

  for (int i = 8; i >= 0; --i) {
    for (int j = 1; j <= 9; ++j) {
      int pos = 1 + 4 * (j - 1);
      if (input[i][pos] != ' ') {
        stacks[j].push(input[i][pos]);
      }
    }
  }
  regex reg(R"(move ([0-9]+) from ([0-9]+) to ([0-9]+))");
  for (int i = 10; i < input.size(); ++i) {
    smatch match;
    if (regex_search(input[i], match, reg)) {
      int val = ToInt(match[1]);
      int from = ToInt(match[2]);
      int to = ToInt(match[3]);

      for (int v = 0; v < val && !stacks[from].empty(); ++v) {
        char crate = stacks[from].top();
        stacks[from].pop();
        stacks[to].push(crate);
      }
    }
  }
  string result;
  for (int j = 1; j <= 9; ++j) {
    result.push_back(stacks[j].top());
  }
  return result;
}

std::string y2022::solve_05b(const std::vector<std::string> &input) {
  vector<stack<char>> stacks(10);

  for (int i = 8; i >= 0; --i) {
    for (int j = 1; j <= 9; ++j) {
      int pos = 1 + 4 * (j - 1);
      if (input[i][pos] != ' ') {
        stacks[j].push(input[i][pos]);
      }
    }
  }
  regex reg(R"(move ([0-9]+) from ([0-9]+) to ([0-9]+))");
  for (int i = 10; i < input.size(); ++i) {
    smatch match;
    if (regex_search(input[i], match, reg)) {
      int val = ToInt(match[1]);
      int from = ToInt(match[2]);
      int to = ToInt(match[3]);

      stack<char> tmp;

      for (int v = 0; v < val && !stacks[from].empty(); ++v) {
        char crate = stacks[from].top();
        stacks[from].pop();
        tmp.push(crate);
      }
      while (!tmp.empty()) {
        char crate = tmp.top();
        tmp.pop();
        stacks[to].push(crate);
      }
    }
  }
  string result;
  for (int j = 1; j <= 9; ++j) {
    result.push_back(stacks[j].top());
  }
  return result;
}
