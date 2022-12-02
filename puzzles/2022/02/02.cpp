// Puzzle is available at https://adventofcode.com/2022/day/2
// Keywords:
#include "../2022.hpp"
#include "../../../src/utils.hpp"
using namespace std;

std::string y2022::solve_02a(const std::vector<std::string> &input) {
  int score = 0;
  for (int i = 0; i < input.size(); ++i) {
    if (input[i][0] == 'A') {
      switch(input[i][2]) {
        case 'X': score += 4; break;
        case 'Y': score += 8; break;
        case 'Z': score += 3; break;
      }
    } else if (input[i][0] == 'B') {
      switch(input[i][2]) {
        case 'X': score += 1; break;
        case 'Y': score += 5; break;
        case 'Z': score += 9; break;
      }
    } else if (input[i][0] == 'C') {
      switch(input[i][2]) {
      case 'X': score += 7; break;
      case 'Y': score += 2; break;
      case 'Z': score += 6; break;
      }
    }
  }
  return to_string(score);
}

std::string y2022::solve_02b(const std::vector<std::string> &input) {
  int score = 0;
  for (int i = 0; i < input.size(); ++i) {
    if (input[i][0] == 'A') {
      switch(input[i][2]) {
        case 'X': score += 3; break;
        case 'Y': score += 4; break;
        case 'Z': score += 8; break;
      }
    } else if (input[i][0] == 'B') {
      switch(input[i][2]) {
        case 'X': score += 1; break;
        case 'Y': score += 5; break;
        case 'Z': score += 9; break;
      }
    } else if (input[i][0] == 'C') {
      switch(input[i][2]) {
      case 'X': score += 2; break;
      case 'Y': score += 6; break;
      case 'Z': score += 7; break;
      }
    }
  }
  return to_string(score);
}
