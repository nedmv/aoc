// Puzzle is available at https://adventofcode.com/2023/day/11
// Keywords:
#include "../../../src/utils.hpp"
#include "../2023.hpp"
using namespace std;

struct Vec2d {
  int x;
  int y;

  long long distance(Vec2d &other) {
    return abs(other.x - x) + abs(other.y - y);
  }
};

std::string y2023::solve_11a(const std::vector<std::string> &input) {
  long long ans = 0;

  vector<vector<char>> m;

  for (const auto &line : input) {
    if (line.size() == 0) {
      break;
    }
    vector<char> vec;
    bool expand = true;
    for (const char c : line) {
      vec.push_back(c);
      if (c == '#') {
        expand = false;
      }
    }
    m.push_back(vec);
    if (expand) {
      m.push_back(vec);
    }
  }

  queue<int> to_expand;
  for (int j = 0; j < m[0].size(); ++j) {
    int i;
    for (i = 0; i < m.size(); ++i) {
      if (m[i][j] == '#') {
        break;
      }
    }
    if (i == m.size()) {
      to_expand.push(j);
    }
  }

  int add = 0;
  while (!to_expand.empty()) {
    int id = to_expand.front() + add + 1;
    to_expand.pop();

    for (int i = 0; i < m.size(); ++i) {
      auto it = m[i].begin() + id;
      m[i].insert(it, '.');
    }
    ++add;
  }

  vector<Vec2d> galaxies;

  for (int i = 0; i < m.size(); ++i) {
    for (int j = 0; j < m[0].size(); ++j) {
      if (m[i][j] == '#') {
        galaxies.push_back({i, j});
      }
    }
  }

  for (int i = 0; i < galaxies.size(); ++i) {
    for (int j = i + 1; j < galaxies.size(); ++j) {
      ans += galaxies[i].distance(galaxies[j]);
    }
  }

  return to_string(ans);
}

long long distance2(Vec2d a, Vec2d b, unordered_set<int> rows,
                    unordered_set<int> cols) {
  int expanded_rows = 0;
  int expanded_cols = 0;
  for (int i = min(a.x, b.x) + 1; i < max(a.x, b.x); ++i) {
    if (rows.contains(i)) {
      ++expanded_rows;
    }
  }
  for (int i = min(a.y, b.y) + 1; i < max(a.y, b.y); ++i) {
    if (cols.contains(i)) {
      ++expanded_cols;
    }
  }
  return abs(a.x - b.x) + expanded_rows * 999999 + abs(a.y - b.y) +
         expanded_cols * 999999;
}

std::string y2023::solve_11b(const std::vector<std::string> &input) {
  long long ans = 0;

  vector<vector<char>> m;
  unordered_set<int> exp_rows;
  unordered_set<int> exp_cols;
  int i = 0;
  for (const auto &line : input) {
    if (line.size() == 0) {
      break;
    }
    vector<char> vec;
    bool expand = true;
    for (const char c : line) {
      vec.push_back(c);
      if (c == '#') {
        expand = false;
      }
    }
    m.push_back(vec);
    if (expand) {
      exp_rows.insert(i);
    }
    ++i;
  }

  for (int j = 0; j < m[0].size(); ++j) {
    int i;
    for (i = 0; i < m.size(); ++i) {
      if (m[i][j] == '#') {
        break;
      }
    }
    if (i == m.size()) {
      exp_cols.insert(j);
    }
  }

  vector<Vec2d> galaxies;

  for (int i = 0; i < m.size(); ++i) {
    for (int j = 0; j < m[0].size(); ++j) {
      if (m[i][j] == '#') {
        galaxies.push_back({i, j});
      }
    }
  }

  for (int i = 0; i < galaxies.size(); ++i) {
    for (int j = i + 1; j < galaxies.size(); ++j) {
      ans += distance2(galaxies[i], galaxies[j], exp_rows, exp_cols);
    }
  }

  return to_string(ans);
}
