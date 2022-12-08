// Puzzle is available at https://adventofcode.com/2022/day/8
// Keywords:
#include "../../../src/utils.hpp"
#include "../2022.hpp"
using namespace std;

std::string y2022::solve_08a(const std::vector<std::string> &input) {
  int count = 0;
  vector<vector<bool>> visible(input.size(),
                               vector<bool>(input[0].size(), false));
  vector<char> maxSizeY(input[0].size(), 0);
  for (int i = 0; i < input.size(); ++i) {
    char maxSize = 0;
    for (int j = 0; j < input[0].size(); ++j) {
      if (input[i][j] > maxSize) {
        maxSize = input[i][j];
        visible[i][j] = true;
      }
      if (input[i][j] > maxSizeY[j]) {
        maxSizeY[j] = input[i][j];
        visible[i][j] = true;
      }
    }
    maxSize = 0;
    for (int j = input[0].size() - 1; j >= 0; --j) {
      if (input[i][j] > maxSize) {
        maxSize = input[i][j];
        visible[i][j] = true;
      }
    }
  }
  maxSizeY = vector<char>(input[0].size(), -1);
  for (int i = input.size() - 1; i >= 0; --i) {
    for (int j = 0; j < input[0].size(); ++j) {
      if (input[i][j] > maxSizeY[j]) {
        maxSizeY[j] = input[i][j];
        visible[i][j] = true;
      }
    }
  }
  for (int i = 0; i < input.size(); ++i) {
    for (int j = 0; j < input[0].size(); ++j) {
      if (visible[i][j]) {
        ++count;
      }
    }
  }
  return to_string(count);
}

static int find_score(const std::vector<std::string> &input, int x, int y) {
  char maxVal = input[x][y];
  int total = 1;

  int i = x;
  int score = 0;
  while (true) {
    if (--i >= 0) {
      ++score;
      if (input[i][y] >= maxVal) {
        break;
      }
    } else {
      break;
    }
  }
  total *= score;

  i = x;
  score = 0;
  while (true) {
    if (++i < input.size()) {
      ++score;
      if (input[i][y] >= maxVal) {
        break;
      }
    } else {
      break;
    }
  }
  total *= score;

  int j = y;
  score = 0;
  while (true) {
    if (--j >= 0) {
      ++score;
      if (input[x][j] >= maxVal) {
        break;
      }
    } else {
      break;
    }
  }
  total *= score;

  j = y;
  score = 0;
  while (true) {
    if (++j < input[0].size()) {
      ++score;
      if (input[x][j] >= maxVal) {
        break;
      }
    } else {
      break;
    }
  }
  total *= score;
  return total;
}

std::string y2022::solve_08b(const std::vector<std::string> &input) {
  int maxScore = 0;
  for (int i = 1; i < input.size() - 1; ++i) {
    for (int j = 1; j < input[0].size() - 1; ++j) {
      int score = find_score(input, i, j);
      if (score > maxScore) {
        maxScore = score;
      }
    }
  }
  return to_string(maxScore);
}
