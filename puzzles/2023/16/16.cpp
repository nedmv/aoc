// Puzzle is available at https://adventofcode.com/2023/day/16
// Keywords:
#include "../../../src/utils.hpp"
#include "../2023.hpp"
using namespace std;

// 0 - NORTH, 1 - WEST,  2 - SOUTH, 3 - EAST
static inline vector<vector<int>> get_next_poses(const vector<vector<char>> &m,
                                                 int row, int col, int dir) {
  vector<vector<int>> ans;
  switch (m[row][col]) {
    case '.': {
      switch (dir) {
        case 0:
          ans.push_back({row - 1, col, 0});
          break;
        case 1:
          ans.push_back({row, col - 1, 1});
          break;
        case 2:
          ans.push_back({row + 1, col, 2});
          break;
        case 3:
          ans.push_back({row, col + 1, 3});
          break;
      };
      break;
    }
    case '\\': {
      switch (dir) {
        case 0:
          ans.push_back({row, col - 1, 1});
          break;
        case 1:
          ans.push_back({row - 1, col, 0});
          break;
        case 2:
          ans.push_back({row, col + 1, 3});
          break;
        case 3:
          ans.push_back({row + 1, col, 2});
          break;
      };
      break;
    }
    case '/': {
      switch (dir) {
        case 0:
          ans.push_back({row, col + 1, 3});
          break;
        case 1:
          ans.push_back({row + 1, col, 2});
          break;
        case 2:
          ans.push_back({row, col - 1, 1});
          break;
        case 3:
          ans.push_back({row - 1, col, 0});
          break;
      };
      break;
    }
    case '|': {
      switch (dir) {
        case 0:
          ans.push_back({row - 1, col, 0});
          break;
        case 1:
          ans.push_back({row - 1, col, 0});
          ans.push_back({row + 1, col, 2});
          break;
        case 2:
          ans.push_back({row + 1, col, 2});
          break;
        case 3:
          ans.push_back({row - 1, col, 0});
          ans.push_back({row + 1, col, 2});
          break;
      };
      break;
    }
    case '-': {
      switch (dir) {
        case 0:
          ans.push_back({row, col - 1, 1});
          ans.push_back({row, col + 1, 3});
          break;
        case 1:
          ans.push_back({row, col - 1, 1});
          break;
        case 2:
          ans.push_back({row, col - 1, 1});
          ans.push_back({row, col + 1, 3});
          break;
        case 3:
          ans.push_back({row, col + 1, 3});
          break;
      };
      break;
    }
  }
  return ans;
}

static inline int lightened_tiles(const vector<vector<char>> &m,
                                  const vector<int> &start,
                                  vector<vector<vector<bool>>> &lights) {
  queue<vector<int>> q;
  q.push(start);

  int ans = 0;

  for (auto &row : lights) {
    for (auto &col : row) {
      col[0] = col[1] = col[2] = col[3] = false;
    }
  }

  lights[start[0]][start[1]][start[2]] = true;

  while (!q.empty()) {
    auto v = q.front();
    q.pop();

    auto next = get_next_poses(m, v[0], v[1], v[2]);
    for (const auto &pos : next) {
      if (0 <= pos[0] && pos[0] < m.size() && 0 <= pos[1] &&
          pos[1] < m[0].size() && !lights[pos[0]][pos[1]][pos[2]]) {
        lights[pos[0]][pos[1]][pos[2]] = true;
        q.push(pos);
      }
    }
  }
  for (const auto &row : lights) {
    for (const auto &col : row) {
      if (col[0] || col[1] || col[2] || col[3]) {
        ++ans;
      }
    }
  }
  return ans;
}

std::string y2023::solve_16a(const std::vector<std::string> &input) {
  auto m = char_map(input);
  vector<vector<vector<bool>>> lights(
      m.size(), vector<vector<bool>>(m[0].size(), vector<bool>(4, false)));
  return to_string(lightened_tiles(m, {0, 0, 3}, lights));
}

std::string y2023::solve_16b(const std::vector<std::string> &input) {
  int ans = 0;
  auto m = char_map(input);

  vector<vector<int>> starts;
  int rows = m.size();
  int cols = m[0].size();
  for (int i = 0; i < rows; ++i) {
    starts.push_back({i, 0, 3});
    starts.push_back({i, cols - 1, 1});
  }
  for (int i = 0; i < cols; ++i) {
    starts.push_back({0, i, 2});
    starts.push_back({rows - 1, i, 0});
  }

  vector<vector<vector<bool>>> lights(
      rows, vector<vector<bool>>(cols, vector<bool>(4, false)));
  for (const auto &s : starts) {
    ans = max(ans, lightened_tiles(m, s, lights));
  }
  return to_string(ans);
}
