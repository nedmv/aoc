
#include "utils.hpp"
#include <regex>
#include "../puzzles/headers.hpp"

std::vector<std::string> split(const std::string &line, const std::string &delim) {
  std::vector<std::string> result;
  size_t last = 0;
  size_t next = 0;
  std::string token;
  while ((next = line.find(delim, last)) <= line.size()) {
    token = line.substr(last, next - last);
    result.push_back(token);
    last = next + 1;
  }
  result.push_back(line.substr(last, line.size()));
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

std::vector<long long> ints(const std::string &s) {
  std::regex num(R"(([0-9]+))");
  auto begin = std::sregex_iterator(s.begin(), s.end(), num);
  auto end = std::sregex_iterator();

  std::vector<long long> result;

  for (std::sregex_iterator i = begin; i != end;++i) {
    std::smatch match = *i;
    result.push_back(stoll(match[1].str()));
  }
  return result;
}

std::vector<long long> signed_ints(const std::string &s) {
  std::regex num(R"((-*[0-9]+))");
  auto begin = std::sregex_iterator(s.begin(), s.end(), num);
  auto end = std::sregex_iterator();

  std::vector<long long> result;

  for (std::sregex_iterator i = begin; i != end;++i) {
    std::smatch match = *i;
    result.push_back(stoll(match[1].str()));
  }
  return result;
}

std::vector<std::vector<char>> char_map(const std::vector<std::string> &input) {
  std::vector<std::vector<char>> res;

  for (const auto &line: input) {
    if (line.size() == 0) {
      break;
    }
    std::vector<char> tmp;
    for (const char c: line) {
      tmp.push_back(c);
    }
    res.push_back(tmp);
  }
  return res;
}

void print_map(const std::vector<std::vector<char>> &m) {
  for (const auto &line: m) {
    for (const auto c: line) {
      std::cout << c;
    }
    std::cout << '\n';
  }
  std::cout << std::endl;
}

std::vector<std::vector<std::vector<char>>> char_maps(const std::vector<std::string> &input) {
  std::vector<std::vector<std::vector<char>>> res;
  std::vector<std::vector<char>> cur;
  for (const auto &line: input) {
    if (line.size() == 0) {
      if (cur.size() > 0) {
        res.push_back(cur);
        cur.clear();
      }
    }
    std::vector<char> tmp;
    for (const char c: line) {
      tmp.push_back(c);
    }
    cur.push_back(tmp);
  }
  if (cur.size() > 0) {
    res.push_back(cur);
  }
  return res;
}