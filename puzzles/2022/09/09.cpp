// Puzzle is available at https://adventofcode.com/2022/day/9
// Keywords:
#include <unordered_set>

#include "../../../src/utils.hpp"
#include "../2022.hpp"
using namespace std;

static int countTailPositions(const std::vector<std::string> &input,
                              int knots) {
  vector<int> X(knots, 0);
  vector<int> Y(knots, 0);
  unordered_set<int> tailPos; //use X + 10000 * Y as index of tail position
  tailPos.insert(0);  // start pos
  for (int i = 0; i < input.size(); ++i) {
    if (input[i].empty()) {
      break;
    }
    int steps = stoi(input[i].substr(2));
    int moveX = 0;
    int moveY = 0;
    switch (input[i][0]) {
      case 'D':
        moveY = -1;
        break;
      case 'U':
        moveY = 1;
        break;
      case 'R':
        moveX = 1;
        break;
      case 'L':
        moveX += -1;
        break;
      default:
        break;
    }
    for (int j = 0; j < steps; ++j) {
      X[0] += moveX;
      Y[0] += moveY;
      for (int n = 1; n < knots; ++n) {
        if (abs(X[n - 1] - X[n]) > 1 || abs(Y[n - 1] - Y[n]) > 1) {
          X[n] += sign(X[n - 1] - X[n]);
          Y[n] += sign(Y[n - 1] - Y[n]);
        }
      }
      tailPos.insert(X[knots - 1] + 10000 * Y[knots - 1]);
    }
  }
  return tailPos.size();
}

std::string y2022::solve_09a(const std::vector<std::string> &input) {
  return to_string(countTailPositions(input, 2));
}

std::string y2022::solve_09b(const std::vector<std::string> &input) {
  return to_string(countTailPositions(input, 10));
}
