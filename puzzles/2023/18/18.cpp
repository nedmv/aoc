// Puzzle is available at https://adventofcode.com/2023/day/18
// Keywords:
#include "../../../src/utils.hpp"
#include "../2023.hpp"
using namespace std;

struct Line {
  long long start_x;
  long long start_y;
  long long end_x;
  long long end_y;
};

typedef pair<char, long long> (*parser_t)(const string &);

static long long calc_area(const std::vector<std::string> &input,
                           parser_t parser) {
  vector<Line> lines;
  long long x = 0;
  long long y = 0;

  for (const auto &l : input) {
    auto [dir, dist] = parser(l);
    int row_step = 0;
    int col_step = 0;
    switch (dir) {
      case '3':
        row_step = -1;
        break;
      case '1':
        row_step = 1;
        break;
      case '2':
        col_step = -1;
        break;
      case '0':
        col_step = 1;
        break;
    }

    Line line;
    line.start_x = x;
    line.start_y = y;
    x += row_step * dist;
    y += col_step * dist;
    line.end_x = x;
    line.end_y = y;

    lines.push_back(line);
  }

  long long ans = 0;
  for (auto &l : lines) {
    ans += l.start_x * l.end_y - l.end_x * l.start_y;
  }
  ans = abs(ans);
  for (auto &l : lines) {
    ans += abs(l.start_x - l.end_x) + abs(l.start_y - l.end_y);
  }
  ans /= 2;
  ans += 1;
  return ans;
}

pair<char, long long> get_dir_and_distance_a(const string &l) {
  char dir = l[0];
  long long dist = stoll(l.substr(2));
  switch (dir) {
    case 'U':
      dir = '3';
      break;
    case 'D':
      dir = '1';
      break;
    case 'L':
      dir = '2';
      break;
    case 'R':
      dir = '0';
      break;
  }
  return {dir, dist};
}

pair<char, long long> get_dir_and_distance_b(const string &l) {
  int start_pos = l.find('#') + 1;
  long long dist = stoll(l.substr(start_pos, 5), nullptr, 16);
  char dir = l[start_pos + 5];
  return {dir, dist};
}

std::string y2023::solve_18a(const std::vector<std::string> &input) {
  return to_string(calc_area(input, get_dir_and_distance_a));
}

std::string y2023::solve_18b(const std::vector<std::string> &input) {
  return to_string(calc_area(input, get_dir_and_distance_b));
}