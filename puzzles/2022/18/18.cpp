// Puzzle is available at https://adventofcode.com/2022/day/18
// Keywords:
#include "../../../src/utils.hpp"
#include "../2022.hpp"
using namespace std;

const vector<vector<int>> moves = {{1, 0, 0},  {-1, 0, 0}, {0, 1, 0},
                                   {0, -1, 0}, {0, 0, 1},  {0, 0, -1}};

std::string y2022::solve_18a(const std::vector<std::string> &input) {
  vector<vector<int>> cubes;
  for (int i = 0; i < input.size(); ++i) {
    cubes.push_back(ints(input[i]));
  }

  vector<vector<vector<bool>>> c(
      24, vector<vector<bool>>(24, vector<bool>(24, false)));
  for (auto cube : cubes) {
    c[cube[0] + 1][cube[1] + 1][cube[2] + 1] = true;
  }

  int count = 0;
  for (int i = 0; i < 23; ++i) {
    for (int j = 0; j < 23; ++j) {
      for (int k = 0; k < 23; ++k) {
        if ((c[i][j][k] == true) && (c[i + 1][j][k] == false)) {
          count++;
        }
        if ((c[i][j][k] == false) && (c[i + 1][j][k] == true)) {
          count++;
        }
        if ((c[i][j][k] == true) && (c[i][j + 1][k] == false)) {
          count++;
        }
        if ((c[i][j][k] == false) && (c[i][j + 1][k] == true)) {
          count++;
        }
        if ((c[i][j][k] == true) && (c[i][j][k + 1] == false)) {
          count++;
        }
        if ((c[i][j][k] == false) && (c[i][j][k + 1] == true)) {
          count++;
        }
      }
    }
  }

  return to_string(count);
}

std::string y2022::solve_18b(const std::vector<std::string> &input) {
  vector<vector<int>> cubes;
  for (int i = 0; i < input.size(); ++i) {
    cubes.push_back(ints(input[i]));
  }
  vector<int> maxVal(3, INT_MIN);
  vector<int> minVal(3, INT_MAX);
  for (auto cube : cubes) {
    maxVal[0] = max(maxVal[0], cube[0] + 1);
    maxVal[1] = max(maxVal[1], cube[1] + 1);
    maxVal[2] = max(maxVal[2], cube[2] + 1);

    minVal[0] = min(minVal[0], cube[0] + 1);
    minVal[1] = min(minVal[1], cube[1] + 1);
    minVal[2] = min(minVal[2], cube[2] + 1);
  }
  int X = maxVal[0] - minVal[0] + 3;
  int Y = maxVal[1] - minVal[1] + 3;
  int Z = maxVal[2] - minVal[2] + 3;

  vector<vector<vector<bool>>> c(
      X, vector<vector<bool>>(Y, vector<bool>(Z, false)));
  for (auto cube : cubes) {
    c[cube[0] - minVal[0] + 1][cube[1] - minVal[1] + 1]
     [cube[2] - minVal[2] + 1] = true;
  }

  vector<vector<vector<bool>>> isolated = c;

  set<vector<int>> visited;
  deque<vector<int>> q;
  q.push_back({0, 0, 0});
  visited.insert({0, 0, 0});

  while (!q.empty()) {
    auto cur = q.front();
    q.pop_front();

    for (auto m : moves) {
      vector<int> v = {cur[0] + m[0], cur[1] + m[1], cur[2] + m[2]};

      if (visited.contains(v)) {
        continue;
      }
      if (v[0] < 0 || v[1] < 0 || v[2] < 0 || v[0] >= X || v[1] >= Y ||
          v[2] >= Z) {
        continue;
      }
      if (c[v[0]][v[1]][v[2]] == false) {
        visited.insert(v);
        q.push_back(v);
      }
    }
  }

  for (int i = 0; i < X; ++i) {
    for (int j = 0; j < Y; ++j) {
      for (int k = 0; k < Z; ++k) {
        if ((c[i][j][k] == false) && !visited.contains({i, j, k})) {
          isolated[i][j][k] = true;
        }
      }
    }
  }

  int count = 0;
  for (int i = 0; i < X; ++i) {
    for (int j = 0; j < Y; ++j) {
      for (int k = 0; k < Z; ++k) {
        if (isolated[i][j][k] == false) {
          for (auto m : moves) {
            vector<int> v = {i + m[0], j + m[1], k + m[2]};
            if (v[0] < 0 || v[1] < 0 || v[2] < 0 || v[0] >= X || v[1] >= Y ||
                v[2] >= Z) {
              continue;
            } else {
              if (isolated[v[0]][v[1]][v[2]] == true) {
                count++;
              }
            }
          }
        }
      }
    }
  }
  return to_string(count);
}
