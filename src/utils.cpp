
#include "utils.hpp"

std::vector<int> parseLineOfNumbers(const std::string &line) {
  std::vector<int> result;
  size_t last = 0;
  size_t next = 0;
  std::string token;
  while ((next = line.find(',', last)) <= line.size()) {
    token = line.substr(last, next - last);
    result.push_back(std::stoi(token.c_str()));
    last = next + 1;
  }
  result.push_back(std::stoi(line.substr(last, line.size())));
  return result;
}

size_t binaryStringToDecimal(const std::string &binary) {
  size_t result = 0;
  for (size_t i = 0; i < binary.size(); i++) {
    if (binary[i] == '1') {
      result += std::pow(2, binary.size() - 1 - i);    
    }
  }
  return result;
}

int sign(int val) {
  if (val < 0) {
    return -1;
  }
  if (val > 0) {
    return 1;
  }
  return 0;
}