// Puzzle is available at https://adventofcode.com/2023/day/13
// Keywords:
#include "../../../src/utils.hpp"
#include "../2023.hpp"
using namespace std;

int find_vertical(const vector<vector<char>> &m) {
  for (int i = 1; i < m[0].size(); ++i) {
    int l = i - 1;
    int r = i;
    bool reflects = true;
    while (0 <= l && r < m[0].size() && reflects) {
      for (int k = 0; k < m.size(); ++k) {
        if (m[k][l] != m[k][r]) {
          reflects = false;
          break;
        }
      }
      --l;
      ++r;
    }
    if (reflects) {
      return i;
    }
  }
  return 0;
}

int find_horizontal(const vector<vector<char>> &m) {
  for (int i = 1; i < m.size(); ++i) {
    int l = i - 1;
    int r = i;
    bool reflects = true;
    while (0 <= l && r < m.size() && reflects) {
      for (int k = 0; k < m[0].size(); ++k) {
        if (m[l][k] != m[r][k]) {
          reflects = false;
          break;
        }
      }
      --l;
      ++r;
    }
    if (reflects) {
      return 100 * i;
    }
  }
  return 0;
}

std::string y2023::solve_13a(const std::vector<std::string> &input) {
  long long ans = 0;

  vector<vector<vector<char>>> m;
  m.push_back(vector<vector<char>>());

  int id = 0;

  for (const auto &line : input) {
    if (line.size() == 0) {
      m.push_back(vector<vector<char>>());
      ++id;
    } else {
      m[id].push_back(vector<char>());
      for (const char c : line) {
        m[id].back().push_back(c);
      }
    }
  }

  for (const auto &map : m) {
    int num = find_vertical(map);
    if (num > 0) {
      ans += num;
    } else {
      num = find_horizontal(map);
      ans += num;
    }
  }
  return to_string(ans);
}

vector<int> find_reflections(const vector<vector<char>> &m) {
  vector<int> reflection;
  for (int i = 1; i < m[0].size(); ++i) {
    int l = i - 1;
    int r = i;
    bool reflects = true;
    while (0 <= l && r < m[0].size() && reflects) {
      for (int k = 0; k < m.size(); ++k) {
        if (m[k][l] != m[k][r]) {
          reflects = false;
          break;
        }
      }
      --l;
      ++r;
    }
    if (reflects) {
      reflection.push_back(i);
    }
  }

  for (int i = 1; i < m.size(); ++i) {
    int l = i - 1;
    int r = i;
    bool reflects = true;
    while (0 <= l && r < m.size() && reflects) {
      for (int k = 0; k < m[0].size(); ++k) {
        if (m[l][k] != m[r][k]) {
          reflects = false;
          break;
        }
      }
      --l;
      ++r;
    }
    if (reflects) {
      reflection.push_back(100 * i);
    }
  }

  return reflection;
}

std::string y2023::solve_13b(const std::vector<std::string> &input) {
  long long ans = 0;

  vector<vector<vector<char>>> m;
  m.push_back(vector<vector<char>>());

  int id = 0;

  for (const auto &line : input) {
    if (line.size() == 0) {
      m.push_back(vector<vector<char>>());
      ++id;
    } else {
      m[id].push_back(vector<char>());
      for (const char c : line) {
        m[id].back().push_back(c);
      }
    }
  }

  id = 0;
  for (auto &map : m) {
    int base = 0;
    int num = find_vertical(map);
    if (num > 0) {
      base += num;
    } else {
      num = find_horizontal(map);
      base += num;
    }

    bool found = false;

    for (int i = 0; i < map.size(); ++i) {
      for (int j = 0; j < map[0].size(); ++j) {
        map[i][j] = (map[i][j] == '#') ? '.' : '#';
        auto refl = find_reflections(map);
        map[i][j] = (map[i][j] == '#') ? '.' : '#';
        if (refl.size() == 0) {
          continue;
        }
        if (refl.size() == 1 && refl[0] != base) {
          ans += refl[0];
          found = true;
          break;
        } else if (refl.size() == 2 && refl[0] == base) {
          ans += refl[1];
          found = true;
          break;
        } else if (refl.size() == 2 && refl[1] == base) {
          ans += refl[0];
          found = true;
          break;
        }
      }
      if (found) {
        break;
      }
    }
    ++id;
  }
  return to_string(ans);
}
