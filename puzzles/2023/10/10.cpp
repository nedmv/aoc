// Puzzle is available at https://adventofcode.com/2023/day/10
// Keywords:
#include "../../../src/utils.hpp"
#include "../2023.hpp"
using namespace std;

vector<int> next_pos(const vector<vector<char>> &m, vector<int> pos,
                     vector<int> prev, bool check_prev = true) {
  vector<vector<int>> ans;
  int row = pos[0];
  int col = pos[1];
  if (row >= m.size() || row < 0 || col >= m[0].size() || col < 0) {
    return vector<int>();
  }

  switch (m[row][col]) {
    case '.':
      break;
    case '|':
      if (row - 1 >= 0) {
        ans.push_back({row - 1, col});
      }
      if (row + 1 < m.size()) {
        ans.push_back({row + 1, col});
      }
      break;
    case '-':
      if (col - 1 >= 0) {
        ans.push_back({row, col - 1});
      }
      if (col + 1 < m[0].size()) {
        ans.push_back({row, col + 1});
      }
      break;
    case 'L':
      if (row - 1 >= 0) {
        ans.push_back({row - 1, col});
      }
      if (col + 1 < m[0].size()) {
        ans.push_back({row, col + 1});
      }
      break;
    case 'J':
      if (row - 1 >= 0) {
        ans.push_back({row - 1, col});
      }
      if (col - 1 >= 0) {
        ans.push_back({row, col - 1});
      }
      break;
    case '7':
      if (row + 1 < m.size()) {
        ans.push_back({row + 1, col});
      }
      if (col - 1 >= 0) {
        ans.push_back({row, col - 1});
      }
      break;
    case 'F':
      if (row + 1 < m.size()) {
        ans.push_back({row + 1, col});
      }
      if (col + 1 < m[0].size()) {
        ans.push_back({row, col + 1});
      }
      break;
  }

  if (ans.size() == 2) {
    if (check_prev) {
      if (ans[0][0] == prev[0] && ans[0][1] == prev[1]) {
        return ans[1];
      } else if (ans[1][0] == prev[0] && ans[1][1] == prev[1]) {
        return ans[0];
      }
    }
    return ans[0];
  }

  return vector<int>();
}

vector<int> find_start(const vector<vector<char>> &m) {
  for (int i = 0; i < m.size(); ++i) {
    for (int j = 0; j < m[0].size(); ++j) {
      if (m[i][j] == 'S') {
        return vector<int>({i, j});
      }
    }
  }
  return vector<int>();
}

std::string y2023::solve_10a(const std::vector<std::string> &input) {
  int ans = 0;

  vector<vector<char>> m;
  for (const auto &l : input) {
    if (l.empty()) {
      break;
    }
    vector<char> local;
    for (const auto c : l) {
      local.push_back(c);
    }
    m.push_back(local);
  }

  auto start = find_start(m);

  string pipes = "|-LJ7F";

  for (auto c : pipes) {
    m[start[0]][start[1]] = c;

    int steps = 1;
    auto pos = next_pos(m, start, start, false);
    auto prev = start;
    if (pos.size() > 0) {
      do {
        auto next = next_pos(m, pos, prev);
        if (next.size() == 0) {
          steps = 0;
          break;
        }
        prev = pos;
        pos = next;
        ++steps;
      } while (pos != start);
    }

    ans = max(ans, steps / 2);
  }

  return to_string(ans);
}

bool is_vertical(char c) {
  static const string vertical_pipes = "|LJ7F";
  return vertical_pipes.find(c) != string::npos;
}

bool goes_up(char c) {
  static const string pipes = "|LJ";
  return pipes.find(c) != string::npos;
}

bool goes_down(char c) {
  static const string pipes = "|7F";
  return pipes.find(c) != string::npos;
}

bool goes_left(char c) {
  static const string pipes = "-7J";
  return pipes.find(c) != string::npos;
}

bool goes_right(char c) {
  static const string pipes = "-LF";
  return pipes.find(c) != string::npos;
}

bool is_horizontal(char c) {
  static const string horizontal_pipes = "-LJ7F";
  return horizontal_pipes.find(c) != string::npos;
}

std::string y2023::solve_10b(const std::vector<std::string> &input) {
  int ans = 0;

  vector<vector<char>> m;
  for (const auto &l : input) {
    if (l.empty()) {
      break;
    }
    vector<char> local;
    for (const auto c : l) {
      local.push_back(c);
    }
    m.push_back(local);
  }

  auto start = find_start(m);

  string pipes = "|-LJ7F";

  vector<vector<int>> loop;
  char chosen_pipe;

  for (auto c : pipes) {
    m[start[0]][start[1]] = c;

    int steps = 1;
    auto pos = next_pos(m, start, start, false);
    auto prev = start;
    vector<vector<int>> local_loop;
    if (pos.size() > 0) {
      local_loop.push_back(start);
      do {
        local_loop.push_back(pos);
        auto next = next_pos(m, pos, prev);
        if (next.size() == 0) {
          steps = 0;
          break;
        }
        prev = pos;
        pos = next;
        ++steps;
      } while (pos != start);
    }
    if (steps / 2 > ans) {
      ans = steps / 2;
      loop = local_loop;
      chosen_pipe = c;
    }
  }

  m[start[0]][start[1]] = 'J';

  set<vector<int>> visited;
  for (auto &l : loop) {
    visited.insert(l);
  }

  auto loop_parts = visited;
  const vector<int> moves = {1, 0, -1, 0, 1};

  vector<vector<char>> sqm(m.size() * 2 - 1,
                           vector<char>(m[0].size() * 2 - 1, ' '));
  for (int i = 0; i < m.size(); ++i) {
    for (int j = 0; j < m[0].size(); ++j) {
      sqm[i * 2][j * 2] = m[i][j];
    }
  }

  set<vector<int>> sqm_loop_parts;
  for (const auto &l : loop_parts) {
    sqm_loop_parts.insert({l[0] * 2, l[1] * 2});
  }

  bool coutFirst = true;
  for (int i = 1; i < sqm.size() - 1; i += 1) {
    for (int j = 1; j < sqm[0].size() - 1; j += 1) {
      if (sqm[i][j] != ' ') {
        continue;
      }
      vector<int> val{i, j};
      vector<int> l{i, j - 1};
      vector<int> r{i, j + 1};
      vector<int> u{i - 1, j};
      vector<int> d{i + 1, j};

      if (sqm_loop_parts.contains(l) && goes_right(sqm[l[0]][l[1]]) &&
          sqm_loop_parts.contains(r) && goes_left(sqm[r[0]][r[1]])) {
        sqm[i][j] = '-';
        sqm_loop_parts.insert(val);
      } else if (sqm_loop_parts.contains(u) && goes_down(sqm[u[0]][u[1]]) &&
                 sqm_loop_parts.contains(d) && goes_up(sqm[d[0]][d[1]])) {
        sqm[i][j] = '|';
        sqm_loop_parts.insert(val);
      }
    }
  }

  queue<vector<int>> q;
  q.push({0, 0});
  auto sqm_seen = sqm_loop_parts;

  sqm_seen.insert({0, 0});

  int count = 0;
  while (!q.empty()) {
    auto v = q.front();
    q.pop();
    if (sqm[v[0]][v[1]] != ' ') {
      ++count;
    }

    for (int i = 0; i < 4; ++i) {
      int row = v[0] + moves[i];
      int col = v[1] + moves[i + 1];

      if (0 <= row && row < sqm.size() && 0 <= col && col < sqm[0].size() &&
          !sqm_seen.contains({row, col})) {
        sqm_seen.insert({row, col});
        q.push({row, col});
      }
    }
  }

  int ignored = 0;
  for (int i = 0; i < sqm.size(); ++i) {
    for (int j = 0; j < sqm[0].size(); ++j) {
      if (sqm[i][j] == ' ') {
        ++ignored;
      }
    }
  }

  int enclosed =
      sqm.size() * sqm[0].size() - sqm_loop_parts.size() - count - ignored;
  return to_string(enclosed);
}
