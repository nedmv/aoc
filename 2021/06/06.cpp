// Puzzle is available at https://adventofcode.com/2021/day/06
// Keywords:
#include "../2021.hpp"
using namespace std;

static vector<int> parseLineOfNumbers(std::string line) {
  vector<int> result;
  size_t last = 0;
  size_t next = 0;
  std::string token;
  while ((next = line.find(',', last)) <= line.size()) {
    token = line.substr(last, next - last);
    result.push_back(stoi(token.c_str()));
    last = next + 1;
  }
  result.push_back(stoi(line.substr(last, line.size())));
  return result;
}

// each fish has it's own counter, works only for low fish amounts
size_t countFishNaive(const std::string &initialState, int lastDay) {
  vector<int> fish = parseLineOfNumbers(initialState);

  for (size_t day = 0; day < lastDay; day++) {
    vector<int> newFish;
    for (auto &&f : fish) {
      if (f != 0) {
        f--;
      } else {
        f = 6;
        newFish.push_back(8);
      }
    }
    fish.insert(fish.end(), newFish.begin(), newFish.end());
  }
  return fish.size();
}

size_t countFish(const std::string &initialState, int lastDay) {
  vector<int> fish = parseLineOfNumbers(initialState);
  vector<size_t> counters(9, 0);
  for (auto &&f : fish) {
    counters[f]++;
  }

  for (size_t day = 0; day < lastDay; day++) {
    size_t tmp = counters[0];
    for (int state = 0; state < 8; state++) {
      counters[state] = counters[state + 1];
    }
    counters[8] = tmp;
    counters[6] += tmp;
  }

  size_t count = 0;
  for (auto &c : counters) {
    count += c;
  }
  return count;
}

const std::string y2021::solve_06a(std::vector<std::string> input) {
  return to_string(countFish(input[0], 80));
}

const std::string y2021::solve_06b(std::vector<std::string> input) {
  return to_string(countFish(input[0], 256));
}