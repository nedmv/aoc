// Puzzle is available at https://adventofcode.com/2021/day/13
// Keywords: regex, set
#include <regex>
#include <set>

#include "../../../src/utils.hpp"
#include "../2021.hpp"
using namespace std;

struct Point {
  Point() : x(0), y(0) {}
  Point(int x, int y) : x{x}, y{y} {}
  ~Point() {}
  int x;
  int y;
  friend bool operator==(const Point &p1, const Point &p2) {
    bool result = false;
    if ((p1.x == p2.x) && (p1.y == p2.y)) {
      result = true;
    }
    return result;
  }
  friend bool operator<(const Point &p1, const Point &p2) {
    bool result = false;
    if (1500 * p1.x + p1.y < 1500 * p2.x + p2.y) {
      result = true;
    }
    return result;
  }
};

class Fold {
 public:
  Fold(char dir, int val) : direction{dir}, value{val} {}
  ~Fold() {}
  char direction;
  int value;
  set<Point> fold(const set<Point> &dots) {
    set<Point> newDots;
    for (auto it = dots.begin(); it != dots.end(); ++it) {
      Point p(it->x, it->y);
      if (direction == 'x') {
        if (it->x == value) {
          continue;
        } else if (it->x > value) {
          p.x = 2 * value - it->x;
        }
      } else if (direction == 'y') {
        if (it->y == value) {
          continue;
        } else if (it->y > value) {
          p.y = 2 * value - it->y;
        }
      }
      newDots.insert(p);
    }
    return newDots;
  }
};

std::string y2021::solve_13a(const std::vector<std::string> &input) {
  set<Point> dots;
  regex dot(R"(([0-9]+),([0-9]+))");
  smatch match;
  size_t i = 0;
  while (!input[i].empty()) {
    regex_match(input[i], match, dot);
    i++;
    dots.insert(Point(ToInt(match[1]), ToInt(match[2])));
  }
  i++;
  vector<Fold> folds;
  regex fold(R"(fold along ([xy]?)=([0-9]+))");
  for (; i < input.size(); i++) {
    regex_match(input[i], match, fold);
    folds.push_back(Fold(match[1].str()[0], ToInt(match[2])));
  }
  auto newDots = folds[0].fold(dots);

  return to_string(newDots.size());
}

static const std::string visualize(set<Point> &dots) {
  string output;
  vector<vector<char>> result(6, vector(dots.rbegin()->x, '.'));
  for (auto it = dots.begin(); it != dots.end(); it++) {
    result[it->y][it->x] = '#';
  }
  output.append("\n");
  for (int i = 0; i < result.size(); i++) {
    for (int j = 0; j < result[0].size(); j++) {
      output.push_back(result[i][j]);
    }
    output.append("\n");
  }
  return output;
}

std::string y2021::solve_13b(const std::vector<std::string> &input) {
  set<Point> dots;
  regex dot(R"(([0-9]+),([0-9]+))");
  smatch match;
  size_t i = 0;
  while (!input[i].empty()) {
    regex_match(input[i], match, dot);
    i++;
    dots.insert(Point(ToInt(match[1]), ToInt(match[2])));
  }
  i++;
  vector<Fold> folds;
  regex fold(R"(fold along ([xy]?)=([0-9]+))");
  for (; i < input.size(); i++) {
    regex_match(input[i], match, fold);
    folds.push_back(Fold(match[1].str()[0], ToInt(match[2])));
  }
  for (int k = 0; k < folds.size(); k++) {
    dots = folds[k].fold(dots);
  }
  return visualize(dots);
}
