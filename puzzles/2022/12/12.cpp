// Puzzle is available at https://adventofcode.com/2022/day/12
// Keywords: BFS
#include "../../../src/utils.hpp"
#include "../2022.hpp"
using namespace std;

static int bfs(const std::vector<std::string> &input, int startY, int startX) {
  const vector<int> dirs = {1, 0, -1, 0, 1};
  deque<vector<int>> q;
  q.push_back({startY, startX, 0});
  set<vector<int>> visited;
  while (!q.empty()) {
    auto cur = q.front();
    q.pop_front();

    char val = input[cur[0]][cur[1]];

    for (int i = 0; i < 4; ++i) {
      int y = cur[0] + dirs[i];
      int x = cur[1] + dirs[i + 1];

      if (visited.contains({y, x})) {
        continue;
      } else if (y >= 0 && y < input.size() && x >= 0 && x < input[0].size()) {
        if (input[y][x] == 'E') {
          if (val == 'y' || val == 'z') {
            return cur[2] + 1;
          } else {
            continue;
          }
        }
        if (val == 'S') {
          if (input[y][x] == 'a' || input[y][x] == 'b') {
            q.push_back({y, x, cur[2] + 1});
            visited.insert({y, x});
          } else {
            continue;
          }
        }
        if ((input[y][x] == 'S') || (val >= input[y][x]) ||
            (val + 1 == input[y][x])) {
          q.push_back({y, x, cur[2] + 1});
          visited.insert({y, x});
        }
      }
    }
  }
  return INT_MAX;
}

std::string y2022::solve_12a(const std::vector<std::string> &input) {
  int startX = 0;
  int startY = 0;
  for (int i = 0; i < input.size(); ++i) {
    for (int j = 0; j < input[0].size(); ++j) {
      if (input[i][j] == 'S') {
        startY = i;
        startX = j;
      }
    }
  }
  return to_string(bfs(input, startY, startX));
}

std::string y2022::solve_12b(const std::vector<std::string> &input) {
  vector<vector<int>> starts;
  for (int i = 0; i < input.size(); ++i) {
    for (int j = 0; j < input[0].size(); ++j) {
      if (input[i][j] == 'S' || input[i][j] == 'a') {
        starts.push_back({i, j});
      }
    }
  }

  int bestResult = INT_MAX;
  for (auto start : starts) {
    int result = bfs(input, start[0], start[1]);
    if (bestResult > result) {
      bestResult = result;
    }
  }
  return to_string(bestResult);
}
