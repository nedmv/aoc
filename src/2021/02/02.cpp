// Puzzle is available at https://adventofcode.com/2021/day/2
// Keywords: regex
#include "../2021.hpp"
#include <regex>
using namespace std;

std::string y2021::solve_02a(const std::vector<std::string> &input) {
  regex reg(R"(([a-z]+) ([0-9]+))");
  smatch match;
  int position = 0;
  int depth = 0;

  for (int i = 0; i < input.size(); i++) {
    regex_match(input[i], match, reg);
    std::string command = match[1].str();
    int value = stoi(match[2].str());

    if (command == "forward") {
      position += value;
    } else if (command == "down") {
      depth += value;
    } else if (command == "up") {
      depth -= value;
    }
  }

  return to_string(position*depth);
}

std::string y2021::solve_02b(const std::vector<std::string> &input) {
  regex reg(R"(([a-z]+) ([0-9]+))");
  smatch match;
  int position = 0;
  int depth = 0;
  int aim = 0;

  for (int i = 0; i < input.size(); i++) {
    regex_match(input[i], match, reg);
    std::string command = match[1].str();
    int value = stoi(match[2].str());

    if (command == "forward") {
      position += value;
      depth += value * aim;
    } else if (command == "down") {
      aim += value;
    } else if (command == "up") {
      aim -= value;
    }
  }

  return to_string(position*depth);
}
