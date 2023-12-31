// Puzzle is available at https://adventofcode.com/2023/day/2
// Keywords:
#include "../../../src/utils.hpp"
#include "../2023.hpp"
using namespace std;

std::string y2023::solve_02a(const std::vector<std::string> &input) {
  int ans = 0;
  unordered_map<char, int> limits = {{'r', 12}, {'g', 13}, {'b', 14}};

  for (int i = 0; i < input.size(); ++i) {
    regex rgb(R"( ([0-9]+) ([rgb]))");
    auto begin = std::sregex_iterator(input[i].begin(), input[i].end(), rgb);
    auto end = std::sregex_iterator();
    bool isGood = true;
    for (std::sregex_iterator it = begin; it != end; ++it) {
      smatch match = *it;
      char c = match[2].str()[0];
      int val = stoi(match[1].str());
      if (val > limits[c]) {
        isGood = false;
        break;
      }
    }
    if (isGood) {
      ans += i + 1;
    }
  }
  return to_string(ans);
}

std::string y2023::solve_02b(const std::vector<std::string> &input) {
  int ans = 0;

  for (int i = 0; i < input.size(); ++i) {
    unordered_map<char, int> limits;
    regex rgb(R"( ([0-9]+) ([rgb]))");
    auto begin = std::sregex_iterator(input[i].begin(), input[i].end(), rgb);
    auto end = std::sregex_iterator();

    for (std::sregex_iterator it = begin; it != end; ++it) {
      smatch match = *it;
      char c = match[2].str()[0];
      int val = stoi(match[1].str());
      limits[c] = max(limits[c], val);
    }
    ans += limits['r'] * limits['g'] * limits['b'];
  }
  return to_string(ans);
}
