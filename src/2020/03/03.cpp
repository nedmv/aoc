// Puzzle is available at https://adventofcode.com/2020/day/3
// Keywords: OOP
#include "../2020.hpp"
using namespace std;

class Toboggan {
 public:
  Toboggan() : _x{0}, _y{0} {}
  Toboggan(int x, int y) : _x{x}, _y{y} {}
  ~Toboggan() {}

  bool move(int x, int y, size_t width, size_t height) {
    int x_new = _x + x;
    int y_new = _y + y;

    if ((x_new < 0) || (y_new < 0) || (y_new >= height)) return false;

    if (x_new >= width) x_new -= width;

    _x = x_new;
    _y = y_new;
    return true;
  }

  int getX() { return _x; }

  int getY() { return _y; }

 private:
  int _x;
  int _y;
};

static size_t count_trees(std::vector<std::string> &input, int moveX, int moveY) {
  size_t height = input.size();
  size_t width = input[0].length();
  size_t trees = 0;
  Toboggan t = Toboggan();

  while (t.move(moveX, moveY, width, height)) {
    if (input[t.getY()].at(t.getX()) == '#') trees++;
  }

  return trees;
}

const std::string y2020::solve_03a(const std::vector<std::string> &input) {
  return to_string(count_trees(const_cast<std::vector<std::string>&>(input), 3, 1));
}

const std::string y2020::solve_03b(const std::vector<std::string> &input) {
  size_t result = 1;
  result *= count_trees(const_cast<std::vector<std::string>&>(input), 1, 1);
  result *= count_trees(const_cast<std::vector<std::string>&>(input), 3, 1);
  result *= count_trees(const_cast<std::vector<std::string>&>(input), 5, 1);
  result *= count_trees(const_cast<std::vector<std::string>&>(input), 7, 1);
  result *= count_trees(const_cast<std::vector<std::string>&>(input), 1, 2);
  return to_string(result);
}
