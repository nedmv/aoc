// Puzzle is available at https://adventofcode.com/2023/day/21
// Keywords:
#include "../../../src/utils.hpp"
#include "../2023.hpp"
using namespace std;

long long calc_map_fill(const vector<vector<char>> &m, vector<long long> start,
                        long long steps) {
  set<vector<long long>> cur;
  cur.insert(start);
  long long step = 0;

  vector<long long> dirs = {1, 0, -1, 0, 1};

  while (step < steps) {
    set<vector<long long>> next;
    for (const auto &e : cur) {
      for (long long i = 0; i < 4; ++i) {
        long long x = e[0] + dirs[i];
        long long y = e[1] + dirs[i + 1];

        if (0 <= x && x < m.size() && 0 <= y && y < m[0].size() &&
            m[x][y] != '#') {
          next.insert({x, y});
        }
      }
    }
    cur = next;
    ++step;
  }
  return cur.size();
}

long long circle_square(long long odd, long long even, long long r) {
  return (r + 1) * (r + 1) * odd + r * r * even;
}

std::string y2023::solve_21a(const std::vector<std::string> &input) {
  auto m = char_map(input);

  vector<long long> start = {0, 0};
  for (int i = 0; i < m.size(); ++i) {
    for (int j = 0; j < m[0].size(); ++j) {
      if (m[i][j] == 'S') {
        start[0] = i;
        start[1] = j;
      }
    }
  }

  return to_string(calc_map_fill(m, start, 64));
}

std::string y2023::solve_21b(const std::vector<std::string> &input) {
  long long ans;
  auto m = char_map(input);
  long long steps = 26501365;
  long long full = m.size();
  long long half = (m.size() - 1) / 2;
  long long filled_squares_r = (steps - half) / m.size();

  vector<long long> start = {0, 0};
  for (int i = 0; i < m.size(); ++i) {
    for (int j = 0; j < m[0].size(); ++j) {
      if (m[i][j] == 'S') {
        start[0] = i;
        start[1] = j;
      }
    }
  }

  long long odd = calc_map_fill(m, start, full);
  long long even = calc_map_fill(m, start, full + 1);

  auto sq = circle_square(odd, even, filled_squares_r);

  long long even_lu = calc_map_fill(m, {0, 0}, half - 1);
  long long even_ld = calc_map_fill(m, {full - 1, 0}, half - 1);
  long long even_ru = calc_map_fill(m, {0, full - 1}, half - 1);
  long long even_rd = calc_map_fill(m, {full - 1, full - 1}, half - 1);
  long long odd_lu = calc_map_fill(m, {0, 0}, half - 2);
  long long odd_ld = calc_map_fill(m, {full - 1, 0}, half - 2);
  long long odd_ru = calc_map_fill(m, {0, full - 1}, half - 2);
  long long odd_rd = calc_map_fill(m, {full - 1, full - 1}, half - 2);

  auto r = filled_squares_r;
  long long total = sq;

  long long corners_odd = odd_lu + odd_ld + odd_ru + odd_rd;
  long long corners_even = even_lu + even_ld + even_ru + even_rd;

  total -= (r + 1) * corners_odd;
  total += r * corners_even;

  return to_string(total);
}
