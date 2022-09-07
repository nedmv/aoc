#include "../2020.hpp"
using namespace std;

/**
 * @brief
 * Debug: ~1 second
 * Release: ~0.7 seconds
 *
 */
size_t solveUsingVector(const vector<string> &input, size_t last_num) {
  string s;
  vector<size_t> data(last_num + 1, 0);
  size_t prev;
  size_t next;
  size_t pos = 1;

  for (size_t i = 0; i < input.size(); i++) {
    s = input[i];
    size_t begin = 0;
    size_t end = s.find(",");
    while (true) {
      prev = stoi(s.substr(begin, end - begin));
      if (end == s.npos) break;  // intentionally don't insert last number here
      data[prev] = pos;
      pos++;
      begin = end + 1;
      end = s.find(",", begin);
    }
  }
  for (; pos < last_num; pos++) {
    size_t value = data[prev];
    if (value) {
      next = pos - value;
    } else {
      next = 0;
    }
    data[prev] = pos;
    prev = next;
  }
  return next;
}

/**
 * @brief
 * Debug: ~23 seconds
 * Release: ~10 seconds
 *
 */
size_t solveUsingMap(const vector<string> &input, size_t last_num) {
  string s;
  map<size_t, size_t> data;  // 0 - num, 1 - last pos.
  map<size_t, size_t>::iterator it;
  size_t prev;
  size_t next;
  size_t pos = 0;

  for (size_t i = 0; i < input.size(); i++) {
    s = input[i];
    size_t begin = 0;
    size_t end = s.find(",");
    while (true) {
      prev = stoi(s.substr(begin, end - begin));
      if (end == s.npos) break;  // intentionally don't insert last number here
      data.insert_or_assign(prev, pos);
      pos++;
      begin = end + 1;
      end = s.find(",", begin);
    }
  }
  for (; pos < last_num - 1; pos++) {
    it = data.find(prev);
    if (it != data.end()) {
      next = pos - (*it).second;
      (*it).second = pos;
    } else {
      next = 0;
      data[prev] = pos;
    }
    prev = next;
  }
  return next;
}

/**
 * @brief
 * Debug: ~5 seconds
 * Release: ~1.7 seconds
 *
 */
size_t solveUsingUnorderedMap(const vector<string> &input, size_t last_num) {
  string s;
  unordered_map<size_t, size_t> data;  // 0 - num, 1 - last pos.
  unordered_map<size_t, size_t>::iterator it;
  data.reserve(last_num);
  size_t prev;
  size_t next;
  size_t pos = 0;

  for (size_t i = 0; i < input.size(); i++) {
    s = input[i];
    size_t begin = 0;
    size_t end = s.find(",");
    while (true) {
      prev = stoi(s.substr(begin, end - begin));
      if (end == s.npos) break;  // intentionally don't insert last number here
      data.insert_or_assign(prev, pos);
      pos++;
      begin = end + 1;
      end = s.find(",", begin);
    }
  }
  for (; pos < last_num - 1; pos++) {
    it = data.find(prev);
    if (it != data.end()) {
      next = pos - (*it).second;
      (*it).second = pos;
    } else {
      next = 0;
      data[prev] = pos;
    }
    prev = next;
  }
  return next;
}

const std::string y2020::solve_15a(const std::vector<std::string> &input) {
  return to_string(solveUsingVector(const_cast<std::vector<std::string>&>(input), 2020));
}

const std::string y2020::solve_15b(const std::vector<std::string> &input) {
  return to_string(solveUsingVector(const_cast<std::vector<std::string>&>(input), 30000000));
}
