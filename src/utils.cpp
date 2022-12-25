
#include "utils.hpp"
#include <regex>

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

int first(const std::string &s, const int invalid) {
  std::regex num(R"((-?[0-9]+))");
  std::smatch match;
  if (std::regex_search(s, match, num)) {
    return stoi(match[1].str());
  } else {
    return invalid;
  }
}

std::vector<int> ints(const std::string &s) {
  std::regex num(R"((-?[0-9]+))");
  auto begin = std::sregex_iterator(s.begin(), s.end(), num);
  auto end = std::sregex_iterator();

  std::vector<int> result;

  for (std::sregex_iterator i = begin; i != end;++i) {
    std::smatch match = *i;
    result.push_back(stoi(match[1].str()));
  }
  return result;
}