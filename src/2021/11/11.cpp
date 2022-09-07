// Puzzle is available at https://adventofcode.com/2021/day/11
// Keywords:
#include "../2021.hpp"
#include "../../utils.hpp"
using namespace std;  

static void increaseAdjacentEnergy(vector<vector<int>> &energy, int i, int j) {
  auto inRange = [](int x, int y){
    return (0 <= x) && (x < 10) && (0 <= y) && (y < 10);
  };
  for (int x = i-1; x <= i+1; x++) {
    for (int y = j-1; y <= j+1; y++) {
      if ((x == i) && (y == j)) {
        continue;
      } else if (inRange(x, y)) {
        energy[x][y]++;
      }
    }
  }
}

static vector<vector<int>> parseEnergy(const std::vector<std::string> &input) {
  vector<vector<int>> energy(10, vector<int>(10, 0));
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      energy[i][j] = input[i][j] - '0';
    }
  }
  return energy;
}

static void incrementEnergy(std::vector<std::vector<int>> &energy) {
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        energy[i][j]++;
      }
    }
}

static void simulateFlashes(vector<vector<int>> &energy) {
  bool flashed;
  do {
    flashed = false;
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        if (energy[i][j] > 9) {
          increaseAdjacentEnergy(energy, i, j);
          flashed = true;
          energy[i][j] = -10; //so adjacent flashes won't make it non negative
        }
      }
    }
  } while (flashed);
}

static size_t countFlashesAndSetEnergyToZero(vector<vector<int>> &energy) {
  size_t flashes = 0;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (energy[i][j] < 0) {
        energy[i][j] = 0;
        flashes++;
      }
    }
  }
  return flashes;
}

std::string y2021::solve_11a(const std::vector<std::string> &input) {
  auto energy = parseEnergy(input);
  size_t flashes = 0;
  for (size_t turn = 0; turn < 100; turn++) {
    incrementEnergy(energy);
    simulateFlashes(energy);
    flashes += countFlashesAndSetEnergyToZero(energy);
  }
  return to_string(flashes);
}

std::string y2021::solve_11b(const std::vector<std::string> &input) {
  auto energy = parseEnergy(input);
  int turn = 0;
  while (true) {
    incrementEnergy(energy);
    simulateFlashes(energy);
    size_t flashes = countFlashesAndSetEnergyToZero(energy);
    turn++;
    if (flashes == 100) {
      break;
    }
  }
  return to_string(turn);
}
