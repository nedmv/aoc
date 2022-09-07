// Puzzle is available at https://adventofcode.com/2021/day/09
// Keywords: recursion
#include "../../utils.hpp"
#include "../2021.hpp"
using namespace std;

bool isLowest(vector<vector<int>> &heightmap, int i, int j) {
  bool check = true;
  if (check && (1 <= i)) {
    check &= (heightmap[i][j] < heightmap[i - 1][j]) ? true : false;
  }
  if (check && (i < heightmap.size() - 1)) {
    check &= (heightmap[i][j] < heightmap[i + 1][j]) ? true : false;
  }
  if (check && (1 <= j)) {
    check &= (heightmap[i][j] < heightmap[i][j - 1]) ? true : false;
  }
  if (check && (j < heightmap[0].size() - 1)) {
    check &= (heightmap[i][j] < heightmap[i][j + 1]) ? true : false;
  }
  // cout << "[" << i << ", " << j << "] " << check << endl;
  return check;
}

uint countBasinSize(const vector<vector<int>> &heightmap,
                    vector<vector<bool>> &basinMap, int i, int j) {
  uint size = 1;  // this point
  basinMap[i][j] = true;
  if ((1 <= i) && !basinMap[i - 1][j] &&
      (heightmap[i][j] < heightmap[i - 1][j]) && (heightmap[i - 1][j] < 9)) {
    size += countBasinSize(heightmap, basinMap, i - 1, j);
  }
  if ((1 <= j) && !basinMap[i][j - 1] &&
      (heightmap[i][j] < heightmap[i][j - 1]) && (heightmap[i][j - 1] < 9)) {
    size += countBasinSize(heightmap, basinMap, i, j - 1);
  }
  if ((i < heightmap.size() - 1) && !basinMap[i + 1][j] &&
      (heightmap[i][j] < heightmap[i + 1][j]) && (heightmap[i + 1][j] < 9)) {
    size += countBasinSize(heightmap, basinMap, i + 1, j);
  }
  if ((j < heightmap[0].size() - 1) && !basinMap[i][j + 1] &&
      (heightmap[i][j] < heightmap[i][j + 1]) && (heightmap[i][j + 1] < 9)) {
    size += countBasinSize(heightmap, basinMap, i, j + 1);
  }
  return size;
}

std::string y2021::solve_09a(const std::vector<std::string> &input) {
  vector<vector<int>> heightmap;
  for (int i = 0; i < input.size(); i++) {
    vector<int> tmp;
    for (int j = 0; j < input[0].size(); j++) {
      tmp.push_back(input[i][j] - '0');
    }
    heightmap.push_back(tmp);
  }
  int count = 0;
  for (int i = 0; i < heightmap.size(); i++) {
    for (int j = 0; j < heightmap[0].size(); j++) {
      if (isLowest(heightmap, i, j)) {
        count += heightmap[i][j];
        count++;
      }
    }
  }
  return to_string(count);
}

std::string y2021::solve_09b(const std::vector<std::string> &input) {
  vector<vector<int>> heightmap;
  for (int i = 0; i < input.size(); i++) {
    vector<int> tmp;
    for (int j = 0; j < input[0].size(); j++) {
      tmp.push_back(input[i][j] - '0');
    }
    heightmap.push_back(tmp);
  }
  vector<int> largestBasins(3, 0);  // sorted in ascending order
  vector<vector<bool>> basinMap(heightmap.size(),
                                vector(heightmap[0].size(), false));

  for (int i = 0; i < heightmap.size(); i++) {
    for (int j = 0; j < heightmap[0].size(); j++) {
      if (isLowest(heightmap, i, j)) {
        uint size = countBasinSize(heightmap, basinMap, i, j);
        if (size > largestBasins[2]) {
          largestBasins[0] = largestBasins[1];
          largestBasins[1] = largestBasins[2];
          largestBasins[2] = size;
        } else if (size > largestBasins[1]) {
          largestBasins[0] = largestBasins[1];
          largestBasins[1] = size;
        } else if (size > largestBasins[0]) {
          largestBasins[0] = size;
        }
      }
    }
  }
  uint count = 1;
  count *= largestBasins[0];
  count *= largestBasins[1];
  count *= largestBasins[2];
  return to_string(count);
}
