// Puzzle is available at https://adventofcode.com/2021/day/08
// Keywords:
#include <algorithm>

#include "../../utils.hpp"
#include "../2021.hpp"
#include <regex>
#include <map>
using namespace std;

int decodeDigit(std::string pattern) {
  static const vector<string> digits = {"abcefg",  "cf",    "acdeg",  "acdfg",
                                        "bcdf",    "abdfg", "abdefg", "acf",
                                        "abcdefg", "abcdfg"};
  std::sort(pattern.begin(), pattern.end());
  int num;
  for (num = 0; num < digits.size(); num++) {
    if (pattern == digits[num]) {
      break;
    }
  }
  return num;
}

int decodeOutput(string &output, const string &decodePattern) {
  map<char, char> decodeMap;

  decodeMap[decodePattern[0]] = 'a';
  decodeMap[decodePattern[1]] = 'b';
  decodeMap[decodePattern[2]] = 'c';
  decodeMap[decodePattern[3]] = 'd';
  decodeMap[decodePattern[4]] = 'e';
  decodeMap[decodePattern[5]] = 'f';
  decodeMap[decodePattern[6]] = 'g';
  decodeMap[' '] = ' ';

  for (int i = 0; i < output.size(); i++) {
    output[i] = decodeMap[output[i]];
  }

  regex reg(R"(([a-g]+) ([a-g]+) ([a-g]+) ([a-g]+))");
  smatch digits;

  regex_match(output, digits, reg);

  return decodeDigit(digits[1].str()) * 1000 +
         decodeDigit(digits[2].str()) * 100 +
         decodeDigit(digits[3].str()) * 10 + 
         decodeDigit(digits[4].str());
}

char findNotExistingElement(const string &input, string elements) {
  for (int i = 0; i < elements.size(); i++) {
    if (input.find(elements[i]) == string::npos) {
      return elements[i];
    }
  }
  return '-';
}

char findFirstDifferentElement(const string &input, char element) {
  int i;
  for (i = 0; i < input.size(); i++) {
    if (input[i] != element) {
      return input[i];
    }
  }
  return '\0';
}

std::string decodeInput(std::string &input) {
  regex reg(R"(([a-g]+) ([a-g]+) ([a-g]+) ([a-g]+) ([a-g]+) ([a-g]+) ([a-g]+) ([a-g]+) ([a-g]+) ([a-g]+))");
  smatch digits;
  regex_match(input, digits, reg);

  string one;
  string four;
  string seven;
  string eight;
  vector<string> digitsWithLengthSix;

  for (size_t i = 1; i <= digits.size(); i++) {
    string digit = digits[i].str();
    if (digit.size() == 2) {
      one = digit;
    } else if (digit.size() == 3) {
      seven = digit;
    } else if (digit.size() == 4) {
      four = digit;
    } else if (digit.size() == 6) {
      digitsWithLengthSix.push_back(digit);
    } else if (digit.size() == 7) {
      eight = digit;
    }
  }

 string decodePattern = "-------";
  string cf = one;
  for (int i = 0; i < seven.size(); i++) {
    if (cf.find(seven[i]) == string::npos) {
      decodePattern[0] = seven[i]; // segment a
      break;
    }
  }

  string bd;
  for (int i = 0; i < four.size(); i++) {
    if (cf.find(four[i]) == string::npos) {
      bd.insert(bd.end(), four[i]);
    }
  }

  string eg;
  for (int i = 0; i < eight.size(); i++) {
    if (cf.find(eight[i]) == string::npos) {
      if (bd.find(eight[i]) == string::npos) {
        if (eight[i] != decodePattern[0]) {
          eg.insert(eg.end(), eight[i]);
        }
      }
    }
  }

  for (int i = 0; i < 3; i++) {
    string currentDigit = digitsWithLengthSix[i];
    char c = findNotExistingElement(currentDigit, cf);
    if (c != '-') { // digit is 6
      decodePattern[2] = c;
      decodePattern[5] = findFirstDifferentElement(cf, c);
    } else {
      c = findNotExistingElement(currentDigit, eg);
      if (c != '-') { // digit is 9
        decodePattern[4] = c;
        decodePattern[6] = findFirstDifferentElement(eg, c);
      } else {
        c = findNotExistingElement(currentDigit, bd);
        if (c != '-') { // digit is 0
          decodePattern[3] = c;
          decodePattern[1] = findFirstDifferentElement(bd, c);
        } else {
          cout << "Parsing error!" << endl;
        }
      }
    }

  }
  return decodePattern;
}

int decode(const std::string &line) {
  string input = line.substr(0, line.find("|") - 1);
  string output = line.substr(line.find("|") + 2, line.size());


  string decodePattern = decodeInput(input);
  int number = decodeOutput(output, decodePattern);
  return number;
}

const std::string y2021::solve_08a(const std::vector<std::string> &input) {
  size_t count = 0;
  for (int i = 0; i < input.size(); i++) {
    string line = input[i].substr(input[i].find("|"), input[i].size() - 1);
    size_t last = 0;
    size_t next = 0;
    while ((next = line.find(' ', last)) <= line.size()) {
      size_t tokenLength = next - last;
      if ((tokenLength == 2) || (tokenLength == 3) || (tokenLength == 4) ||
          (tokenLength == 7)) {
        count++;
      }
      last = next + 1;
    }
    next = line.size();
    size_t tokenLength = next - last;
    if ((tokenLength == 2) || (tokenLength == 3) || (tokenLength == 4) ||
        (tokenLength == 7)) {
      count++;
    }
  }
  return to_string(count);
}

const std::string y2021::solve_08b(const std::vector<std::string> &input) {
  int sum = 0;
  for (int i = 0; i < input.size(); i++) {
    sum += decode(input[i]);
  }
  return to_string(sum);
}
