// Puzzle is available at https://adventofcode.com/2021/day/05
// Keywords: regex
#include <regex>

#include "../2021.hpp"
#include "../../utils.hpp"
using namespace std;
struct Point {
  Point() : x(0), y(0) {}
  Point(int x, int y) : x(x), y(y) {}
  int x;
  int y;
  void print() { cout << "x = " << x << ", y = " << y << "\n"; }
};

/**
 * @brief Count signum(x).
 *
 * @param x
 * @return 1 if x is positive, -1 if x is negative, 0 if x == 0.
 */
int sgn(int x) { return (0 < x) - (x < 0); }

vector<Point> parseLine(const string &line, bool countDiagonals) {
  vector<Point> points;
  regex reg(R"(([0-9]+),([0-9]+) -> ([0-9]+),([0-9]+))");
  smatch match;
  regex_match(line, match, reg);
  Point start(ToInt(match[1]), ToInt(match[2]));
  Point end(ToInt(match[3]), ToInt(match[4]));

  if ((start.x == end.x) || (start.y == end.y) || countDiagonals) {
    for (int i = 0; i <= max(abs(end.x - start.x), abs(end.y - start.y)); i++) {
      points.push_back(Point(start.x + i * sgn(end.x - start.x),
                             start.y + i * sgn(end.y - start.y)));
    }
  }
  return points;
}

const std::string solve(std::vector<std::string> input, bool countDiagonals) {
  // fixed size is not robust, but works for given input
  vector<vector<uint>> counters(1000, vector<uint>(1000, 0));

  for (size_t i = 0; i < input.size(); ++i) {
    vector<Point> line = parseLine(input[i], countDiagonals);
    for (auto &point : line) {
      counters[point.x][point.y]++;
    }
  }
  size_t count = 0;
  for (size_t i = 0; i < counters.size(); ++i) {
    for (size_t j = 0; j < counters[0].size(); ++j) {
      if (counters[i][j] >= 2) {
        count++;
      }
    }
  }
  return to_string(count);
}

const std::string y2021::solve_05a(const std::vector<std::string> &input) {
  return solve(input, false);
}

const std::string y2021::solve_05b(const std::vector<std::string> &input) {
  return solve(input, true);
}
