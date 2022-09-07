// Puzzle is available at https://adventofcode.com/2021/day/03
// Keywords:
#include "../2021.hpp"
#include "../../utils.hpp"
#include <cmath>
using namespace std;


std::string y2021::solve_03a(const std::vector<std::string> &input) {
  size_t len = input[0].size();
  vector<uint> counters(len, 0);

  for (size_t i = 0; i < input.size(); i++) {
    for (size_t j = 0; j < len; j++) {
      if (input[i][j] == '1') {
        counters[j]++;
      }
    }
  }

  size_t gamma = 0;
  size_t epsilon = 0;
  for (size_t i = 0; i < len; i++) {
    if (counters[i] > input.size()/2) {
      gamma += pow(2, len - 1 - i);
    } else {
      epsilon += pow(2, len - 1 - i);
    }
  }

  return to_string(gamma * epsilon);
}

uint determineRate(const std::vector<std::string> &input, bool preferOnes) {
  size_t len = input[0].size();
  vector<bool> eligible(input.size(), true);


  int lastEligible = 0;
  for (size_t i = 0; i < len; i++) {
    uint ones = 0;
    uint total = 0;
    //count ones on pos i for current eligible numbers
    for (size_t j = 0; j < input.size(); j++) {
      if (eligible[j]) {
        total++;
        if (input[j][i] == '1') {
          ones++;
        }
      }
    }
    //prepare next set of eligible numbers
    char eligibleChar;
    if (preferOnes) {
      eligibleChar = (total <= 2*ones) ? '1' : '0';
    } else {
      eligibleChar = (total <= 2*ones) ? '0' : '1';
    }
    uint eligibleCounter = 0;
    uint lastEligibleIndex = 0;
    for (size_t j = 0; j < input.size(); j++) {
      if (eligible[j]) {
        if (input[j][i] == eligibleChar) {
          lastEligibleIndex = j;
          eligibleCounter++;
        } else {
          eligible[j] = false;
        }
      }
    }
    //return last one standing
    if (eligibleCounter == 1) {
      lastEligible = binaryStringToDecimal(input[lastEligibleIndex]);
      break;
    }
  }
  return lastEligible;
}

std::string y2021::solve_03b(const std::vector<std::string> &input) {
  return to_string(determineRate(input, true)*determineRate(input, false));
}
