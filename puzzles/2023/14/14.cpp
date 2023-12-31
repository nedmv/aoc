// Puzzle is available at https://adventofcode.com/2023/day/14
// Keywords:
#include "../../../src/utils.hpp"
#include "../2023.hpp"
using namespace std;

static void roll_north(vector<vector<char>> &m) {
  for (int i = 1; i < m.size(); ++i) {
    for (int j = 0; j < m[0].size(); ++j) {
      if (m[i][j] == 'O') {
        int k = i - 1;
        while (0 <= k && m[k][j] == '.') {
          --k;
        }
        if (k + 1 != i) {
          m[k + 1][j] = 'O';
          m[i][j] = '.';
        }
      }
    }
  }
}

static void roll_south(vector<vector<char>> &m) {
  for (int i = m.size() - 2; i >= 0; --i) {
    for (int j = 0; j < m[0].size(); ++j) {
      if (m[i][j] == 'O') {
        int k = i + 1;
        while (k < m.size() && m[k][j] == '.') {
          ++k;
        }
        if (k - 1 != i) {
          m[k - 1][j] = 'O';
          m[i][j] = '.';
        }
      }
    }
  }
}

static void roll_west(vector<vector<char>> &m) {
  for (int i = 0; i < m.size(); ++i) {
    for (int j = 1; j < m[0].size(); ++j) {
      if (m[i][j] == 'O') {
        int k = j - 1;
        while (0 <= k && m[i][k] == '.') {
          --k;
        }
        if (k + 1 != j) {
          m[i][k + 1] = 'O';
          m[i][j] = '.';
        }
      }
    }
  }
}

static void roll_east(vector<vector<char>> &m) {
  for (int i = 0; i < m.size(); ++i) {
    for (int j = m[0].size() - 2; j >= 0; --j) {
      if (m[i][j] == 'O') {
        int k = j + 1;
        while (k < m[0].size() && m[i][k] == '.') {
          ++k;
        }
        if (k - 1 != j) {
          m[i][k - 1] = 'O';
          m[i][j] = '.';
        }
      }
    }
  }
}

static void roll(vector<vector<char>> &m) {
  roll_north(m);
  roll_west(m);
  roll_south(m);
  roll_east(m);
}

static int calc_load(const vector<vector<char>> &m) {
  int ans = 0;
  for (int i = 0; i < m.size(); ++i) {
    for (int j = 0; j < m[0].size(); ++j) {
      if (m[i][j] == 'O') {
        ans += m.size() - i;
      }
    }
  }
  return ans;
}

static int calc_hash(const vector<vector<char>> &m) {
  int res = 0;
  for (int i = 0; i < m.size(); ++i) {
    for (int j = 0; j < m[0].size(); ++j) {
      if (m[i][j] == 'O') {
        res += (i + 1) * (j + 101);
      }
    }
  }
  return res;
}

std::string y2023::solve_14a(const std::vector<std::string> &input) {
  auto m = char_map(input);
  roll_north(m);
  auto ans = calc_load(m);
  return to_string(ans);
}

std::string y2023::solve_14b(const std::vector<std::string> &input) {
  long long ans = 0;
  const int total = 1e9;

  vector<vector<char>> m = char_map(input);
  vector<int> loads;

  int i = 1;
  unordered_map<int, pair<int, int>> hashes;  // hash -> {index, load}
  int loop_start;
  int loop_size;
  while (true) {
    roll(m);
    auto h = calc_hash(m);
    if (!hashes.contains(h)) {
      hashes[h].first = i;
      hashes[h].second = calc_load(m);
    } else {
      loop_size = i - hashes[h].first;
      loop_start = hashes[h].first;
      break;
    }
    ++i;
  }

  int target = loop_start + (total - loop_start) % loop_size;
  for (const auto &[k, v] : hashes) {
    if (v.first == target) {
      ans = v.second;
      break;
    }
  }
  return to_string(ans);
}
