// Puzzle is available at https://adventofcode.com/2023/day/3
// Keywords:
#include "../../../src/utils.hpp"
#include "../2023.hpp"
using namespace std;

bool check_adj(const vector<string> &input, int row, int col) {
  vector<vector<int>> steps = {{1, 0},  {1, 1},  {1, -1}, {0, 1},
                               {0, -1}, {-1, 0}, {-1, 1}, {-1, -1}};
  queue<vector<int>> q;
  set<vector<int>> visited;
  q.push({row, col});
  visited.insert({row, col});
  while (!q.empty()) {
    auto v = q.front();
    q.pop();
    for (int i = 0; i < steps.size(); ++i) {
      int a = v[0] + steps[i][0];
      int b = v[1] + steps[i][1];
      if (0 <= a && a < input.size() && 0 <= b && b < input[a].size() &&
          !visited.contains({a, b})) {
        visited.insert({a, b});
        char c = input[a][b];
        if (isdigit(c)) {
          q.push({a, b});
        } else if (c == '.') {
          continue;
        } else {
          return true;
        }
      }
    }
  }
  return false;
}

std::string y2023::solve_03a(const std::vector<std::string> &input) {
  int ans = 0;
  int n = input.size();
  for (int i = 0; i < n; ++i) {
    bool adj = false;
    int dots = 0;
    int j = 0;
    while (j < input[i].size()) {
      char c = input[i][j];
      int next_pos = j + 1;
      if (isdigit(c) && check_adj(input, i, j)) {
        while (isdigit(input[i][next_pos])) {
          ++next_pos;
        }

        auto s = input[i].substr(j, next_pos - j + 1);
        int num = stoi(s);
        ans += num;
      }
      j = next_pos;
    }
  }
  return to_string(ans);
}

bool is_gear(const vector<string> &input, int row, int col,
             vector<long long> &nums) {
  vector<vector<int>> steps = {{1, 0},  {1, 1},  {1, -1}, {0, 1},
                               {0, -1}, {-1, 0}, {-1, 1}, {-1, -1}};
  queue<vector<int>> q;
  set<vector<int>> visited;
  q.push({row, col});
  visited.insert({row, col});

  int found_nums = 0;
  vector<int> v = {row, col};
  for (int i = 0; i < steps.size(); ++i) {
    int a = v[0] + steps[i][0];
    int b = v[1] + steps[i][1];
    if (0 <= a && a < input.size() && 0 <= b && b < input[a].size() &&
        !visited.contains({a, b})) {
      visited.insert({a, b});
      char c = input[a][b];
      if (isdigit(c)) {
        ++found_nums;
        if (found_nums > 2) {
          return false;
        }
        visited.insert({a, b});
        int l = b - 1;
        while (0 <= l && isdigit(input[a][l])) {
          visited.insert({a, l});
          --l;
        }
        int r = b + 1;
        while (r < input[a].size() && isdigit(input[a][r])) {
          visited.insert({a, r});
          ++r;
        }
        nums.push_back(stoi(input[a].substr(l + 1, r - l - 1)));
      }
    }
  }
  return found_nums == 2;
}

std::string y2023::solve_03b(const std::vector<std::string> &input) {
  long long ans = 0;
  int n = input.size();
  for (int i = 0; i < n; ++i) {
    bool adj = false;
    int dots = 0;
    for (int j = 0; j < n; ++j) {
      char c = input[i][j];
      vector<long long> nums;
      if (c == '*' && is_gear(input, i, j, nums)) {
        ans += nums[0] * nums[1];
      }
    }
  }
  return to_string(ans);
}
