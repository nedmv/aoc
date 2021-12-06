// Puzzle is available at https://adventofcode.com/2020/day/2
// Keywords: regex
#include "../2020.hpp"
using namespace std;

const std::string y2020::solve_02a(std::vector<std::string> input) {
  // groups: 1 - min, 2 - max, 3 - char, 4 - string
  regex reg(R"(^([0-9]+)-([0-9]+)\s([a-z]?):\s([a-z]+)$)");
  smatch groups;
  size_t correct_passwords = 0;
  for (size_t i = 0; i < input.size(); i++) {
    regex_match(input[i], groups, reg);
    size_t num =
        count(groups[4].first, groups[4].second, groups[3].str().at(0));
    if ((num >= stoi(groups[1].str())) && (num <= stoi(groups[2].str()))) {
      correct_passwords++;
    }
  }
  return to_string(correct_passwords);
}

const std::string y2020::solve_02b(std::vector<std::string> input) {
  // groups: 1 - pos 1, 2 - pos 2, 3 - char, 4 - string
  regex reg(R"(^([0-9]+)-([0-9]+)\s([a-z]?):\s([a-z]+)$)");
  smatch groups;
  size_t correct_passwords = 0;
  for (size_t i = 0; i < input.size(); i++) {
    regex_match(input[i], groups, reg);
    size_t pos1 = stoi(groups[1].str()) - 1;
    size_t pos2 = stoi(groups[2].str()) - 1;
    char c = groups[3].str().at(0);
    string str = groups[4].str();

    if (!(str.at(pos1) == c) != !(str.at(pos2) == c)) {
      correct_passwords++;
    }
  }
  return to_string(correct_passwords);
}
