// Puzzle is available at https://adventofcode.com/2023/day/17
// Keywords:
#include "../../../src/utils.hpp"
#include "../2023.hpp"
using namespace std;

std::string y2023::solve_17a(const std::vector<std::string> &input) {
  int ans = 0;
  auto m = char_map(input);
  vector<int> dirs = {1, 0, -1, 0, 1};

  // We use invalid dir with 3 turns to turn right away from it.
  vector<int> start = {0, 0, 0, -1, 3};  // cost, x, y, prev_dir, prev_turns
  priority_queue<vector<int>, vector<vector<int>>, std::greater<vector<int>>> q;
  q.push(start);

  vector<vector<vector<vector<int>>>> visited(m.size(),
      vector<vector<vector<int>>>(
          m[0].size(), vector<vector<int>>(4, vector<int>(4, INT_MAX))));
  while (!q.empty()) {
    auto e = q.top();
    q.pop();

    if (e[1] == m.size() - 1 && e[2] == m[0].size() - 1) {
      ans = e[0];
      break;
    }

    for (int dir = 0; dir < 4; ++dir) {
      int x = e[1] + dirs[dir];
      int y = e[2] + dirs[dir + 1];
      if (x < 0 || m.size() <= x || y < 0 || m[0].size() <= y) {
        continue;
      }
      int turns = 1;
      if (dir != e[3]) {
        if (e[3] >= 0 && (dir + 2) % 4 == e[3]) {
          continue;  // can't go back
        }
      } else {
        if (e[4] == 3) {
          continue;  // must turn
        }
        turns = e[4] + 1;
      }
      int cost = e[0] + (m[x][y] - '0');
      if (visited[x][y][dir][turns] <=
          cost) {  // check if we already had better path for this cell
        continue;
      }
      visited[x][y][dir][turns] = cost;
      q.push({cost, x, y, dir, turns});
    }
  }

  return to_string(ans);
}

std::string y2023::solve_17b(const std::vector<std::string> &input) {
  int ans = 0;
  auto m = char_map(input);
  vector<int> dirs = {1, 0, -1, 0, 1};

  // We use invalid dir with 4 turns to turn right away from it.
  vector<int> start = {0, 0, 0, -1, 4};  // cost, x, y, prev_dir, prev_turns
  priority_queue<vector<int>, vector<vector<int>>, std::greater<vector<int>>> q;
  q.push(start);

  vector<vector<vector<vector<int>>>> visited(
      m.size(), vector(m[0].size(), vector(4, vector(11, INT_MAX))));

  while (!q.empty()) {
    auto e = q.top();
    q.pop();

    if (e[1] == m.size() - 1 && e[2] == m[0].size() - 1 && e[4] >= 4) {
      ans = e[0];
      break;
    }

    for (int dir = 0; dir < 4; ++dir) {
      int x = e[1] + dirs[dir];
      int y = e[2] + dirs[dir + 1];
      if (x < 0 || m.size() <= x || y < 0 || m[0].size() <= y) {
        continue;
      }
      int turns = 1;
      if (dir != e[3]) {
        if (e[4] < 4) {
          continue;  // can't turn
        }
        if (e[3] >= 0 && (dir + 2) % 4 == e[3]) {
          continue;  // can't go back
        }
      } else {
        if (e[4] == 10) {
          continue;  // must turn
        }
        turns = e[4] + 1;
      }
      int cost = e[0] + (m[x][y] - '0');
      if (visited[x][y][dir][turns] <=
          cost) {  // check if we already had better path for this cell
        continue;
      }
      visited[x][y][dir][turns] = cost;
      q.push({cost, x, y, dir, turns});
    }
  }
  return to_string(ans);
}
