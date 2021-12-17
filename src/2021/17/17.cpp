// Puzzle is available at https://adventofcode.com/2021/day/17
// Keywords: regex, point
#include <regex>
#include "../../utils.hpp"
#include "../2021.hpp"
using namespace std;

struct Rect {
  Rect(int xMin, int xMax, int yMin, int yMax)
      : xMin{xMin}, xMax(xMax), yMin{yMin}, yMax(yMax) {}
  ~Rect() {}
  int xMin, xMax;
  int yMin, yMax;
};

struct Point {
  Point() : x(0), y(0) {}
  Point(int x, int y) : x(x), y(y) {}
  int x;
  int y;
  void print() { cout << "x = " << x << ", y = " << y << "\n"; }
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

struct Probe {
  Probe(int x0, int y0, const Rect &bounds)
      : xVel{x0}, yVel{y0}, bounds{bounds} {}
  ~Probe() {}
  bool move() {
    x += xVel;
    y += yVel;
    if (y > yReached) {
      yReached = y;
    }
    if (xVel > 0) {
      xVel--;
    } else if (xVel < 0) {
      xVel++;
    }
    yVel--;
    return isWithinBounds();
  }
  bool isWithinBounds() {
    return ((bounds.xMin <= x) && (x <= bounds.xMax) && (bounds.yMin <= y) &&
            (y <= bounds.yMax));
  }
  int x = 0;
  int y = 0;
  int yReached = 0;
  int xVel;
  int yVel;
  Rect bounds;
};

static const Rect parseRect(const std::string &input) {
  regex reg(R"(x=([0-9\-]+)\.\.([0-9\-]+), y=([0-9\-]+)\.\.([0-9\-]+))");
  smatch match;

  regex_search(input, match, reg);
  int xMin = ToInt(match[1]);
  int xMax = ToInt(match[2]);
  int yMin = ToInt(match[3]);
  int yMax = ToInt(match[4]);
  const Rect bounds(xMin, xMax, yMin, yMax);
  return bounds;
}


const std::string y2021::solve_17a(std::vector<std::string> input) {
  auto bounds = parseRect(input[0]);
  int yBest = 0;

  //brute force
  for (int i = 0; i <= bounds.xMax; i++) {
    for (int j = bounds.yMin - 1; j < 1000; j++) {
      int yCurrent = 0;
      Probe probe(i, j, bounds);
      while (probe.y >= bounds.yMin) {
        if ((probe.xVel == 0) &&
            ((probe.x < bounds.xMin) || (probe.x > bounds.xMax))) {
          break;
        }
        if (probe.move()) {
          yCurrent = probe.yReached;
          break;
        }
      }
      if (yCurrent > yBest) {
        yBest = yCurrent;
      }
    }
  }
  return to_string(yBest);
}

const std::string y2021::solve_17b(std::vector<std::string> input) {
  auto bounds = parseRect(input[0]);
  size_t count = 0;

  //brute force
  for (int i = 1; i <= bounds.xMax; i++) {
    for (int j = bounds.yMin - 1; j < 1000; j++) {
      Probe probe(i, j, bounds);
      while (probe.y >= bounds.yMin) {
        if ((probe.xVel == 0) &&
            ((probe.x < bounds.xMin) || (probe.x > bounds.xMax))) {
          break;
        }
        if (probe.move()) {
          count++;
          break;
        }
      }
    }
  }
  return to_string(count);
}