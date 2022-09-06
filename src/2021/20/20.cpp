// Puzzle is available at https://adventofcode.com/2021/day/20
// Keywords:
#include "../../utils.hpp"
#include "../2021.hpp"
using namespace std;

// clang-format off
static uint countIndex(vector<vector<bool>> &image, int i, int j) {
  uint index = 256 * image[i - 1][j - 1] + 128 * image[i - 1][j] + 64 * image[i - 1][j + 1] 
               + 32 * image[i][j - 1] + 16 * image[i][j] + 8 * image[i][j + 1] +
               4 * image[i + 1][j - 1] + 2 * image[i + 1][j] + 1 * image[i + 1][j + 1];
  return index;
}
// clang-format on

static size_t countLitPixels(vector<vector<bool>> &image) {
  size_t count = 0;
  for (size_t i = 0; i < image.size(); i++) {
    for (size_t j = 0; j < image[0].size(); j++) {
      if (image[i][j]) {
        count++;
      }
    }
  }
  return count;
}

static void printImage(vector<vector<bool>> &image) {
  for (size_t i = 0; i < image.size(); i++) {
    for (size_t j = 0; j < image[0].size(); j++) {
      if (image[i][j]) {
        cout << "#";
      } else {
        cout << ".";
      }
    }
    cout << "\n";
  }
  cout << endl;
}

static void enlarge(vector<vector<bool>> &image) {
  for (int i = 0; i < image.size(); i++) {
    image[i].insert(image[i].begin(), false);
    image[i].push_back(false);
  }
  image.insert(image.begin(), vector<bool>(image[0].size(), false));
  image.push_back(vector<bool>(image[0].size(), false));
}

static void shrink(vector<vector<bool>> &image) {
  image.erase(image.begin());
  image.pop_back();
  for (int i = 0; i < image.size(); i++) {
    image[i].erase(image[i].begin());
    image[i].pop_back();
  }
}

static void enchance(vector<vector<bool>> &image, vector<bool> &algorithm) {
  vector<vector<bool>> result(image.size(),
                              vector<bool>(image[0].size(), false));
  for (int i = 1; i < result.size() - 1; i++) {
    for (int j = 1; j < result[0].size() - 1; j++) {
      result[i][j] = algorithm[countIndex(image, i, j)];
    }
  }
  image = result;
}

static std::string solve(std::vector<std::string> &input, int iterations) {
  vector<bool> algo(512, false);
  for (size_t i = 0; i < input[0].size(); ++i) {
    if (input[0][i] == '#') {
      algo[i] = true;
    }
  }
  vector<vector<bool>> image(input.size() - 2,
                             vector<bool>(input[2].size(), false));
  for (size_t i = 2; i < input.size(); ++i) {
    for (size_t j = 0; j < input[2].size(); ++j) {
      if (input[i][j] == '#') {
        image[i - 2][j] = true;
      }
    }
  }
  for (size_t i = 0; i < 2 * iterations; i++) {
    enlarge(image);
  }

  for (int i = 0; i < image.size(); i++) {
    image[i].insert(image[i].begin(), false);
    image[i].push_back(false);
  }
  image.insert(image.begin(), vector<bool>(image[0].size(), false));
  image.push_back(vector<bool>(image[0].size(), false));

  for (int i = 0; i < iterations; i++) {
    enchance(image, algo);
    shrink(image);
  }
  return to_string(countLitPixels(image));
}

const std::string y2021::solve_20a(const std::vector<std::string> &input) {
  return solve(const_cast<std::vector<std::string>&>(input), 2);
}

const std::string y2021::solve_20b(const std::vector<std::string> &input) {
  return solve(const_cast<std::vector<std::string>&>(input), 50);
}
