// Puzzle is available at https://adventofcode.com/2021/day/14
// Keywords: set, map
#include <map>
#include <set>

#include "../../../src/utils.hpp"
#include "../2021.hpp"
using namespace std;

struct InsertionRule {
  InsertionRule(char first, char second, char inserted)
      : first{first}, second{second}, inserted{inserted} {}
  ~InsertionRule() {}
  char checkPair(char c1, char c2) {
    char result = ' ';
    if ((c1 == first) && (c2 == second)) {
      result = inserted;
    }
    return result;
  }
  size_t count = 0;
  char first;
  char second;
  char inserted;
};

// naive approach, see 14b for more effective solution
std::string y2021::solve_14a(const std::vector<std::string> &input) {
  string polymer;
  for (int j = 0; j < input[0].size(); j++) {
    polymer.push_back(input[0][j]);
  }
  vector<InsertionRule> rules;
  for (int i = 2; i < input.size(); i++) {
    rules.push_back(InsertionRule(input[i][0], input[i][1], input[i][6]));
  }
  for (int step = 0; step < 10; step++) {
    string newPolymer;
    for (int i = 0; i < polymer.size() - 1; i++) {
      newPolymer.push_back(polymer[i]);
      for (auto &rule : rules) {
        char c = rule.checkPair(polymer[i], polymer[i + 1]);
        if (c != ' ') {
          newPolymer.push_back(c);
          break;
        }
      }
    }
    newPolymer.push_back(*polymer.rbegin());
    polymer = newPolymer;
  }
  set<char> uniq;
  for (char c : polymer) {
    uniq.insert(c);
  }
  vector<size_t> counts(uniq.size(), 0);
  for (char c : polymer) {
    auto cit = counts.begin();
    for (auto it = uniq.begin(); it != uniq.end(); it++) {
      if (*it == c) {
        (*cit)++;
        break;
      }
      cit++;
    }
  }
  sort(counts.begin(), counts.end());
  size_t result = *counts.rbegin() - *counts.begin();
  return to_string(result);
}

std::string y2021::solve_14b(const std::vector<std::string> &input) {
  string polymer;
  for (int j = 0; j < input[0].size(); j++) {
    polymer.push_back(input[0][j]);
  }
  vector<InsertionRule> rules;
  for (int i = 2; i < input.size(); i++) {
    rules.push_back(InsertionRule(input[i][0], input[i][1], input[i][6]));
  }
  for (int i = 0; i < polymer.size() - 1; i++) {
    for (auto &&rule : rules) {
      if ((rule.first == polymer[i]) && (rule.second == polymer[i + 1])) {
        rule.count++;
      }
    }
  }
  for (int step = 0; step < 40; step++) {  // 39 steps
    vector<InsertionRule> newRules = rules;
    for (auto &&newRule : newRules) {
      newRule.count = 0;
    }
    for (auto &rule : rules) {
      for (auto &&newRule : newRules) {
        if (((newRule.first == rule.first) &&
             (newRule.second == rule.inserted)) ||
            ((newRule.first == rule.inserted) &&
             (newRule.second == rule.second))) {
          newRule.count += rule.count;
        }
      }
    }
    rules = newRules;
  }
  map<char, size_t> counts;
  for (auto &rule : rules) {
    counts[rule.first] += rule.count;
    counts[rule.second] += rule.count;
  }
  for (auto &&count : counts) {
    count.second /= 2;
  }
  counts[polymer[0]]++;  // count first and last symbols in polymer
  counts[polymer[polymer.size() - 1]]++;

  const auto [min, max] = std::minmax_element(
      counts.begin(), counts.end(),
      [](const pair<char, size_t> &p1, const pair<char, size_t> &p2) {
        return p1.second < p2.second;
      });
  return to_string(max->second - min->second);
}
