// Puzzle is available at https://adventofcode.com/2023/day/9
// Keywords:
#include "../../../src/utils.hpp"
#include "../2023.hpp"
using namespace std;

std::string y2023::solve_09a(const std::vector<std::string> &input) {
  long long ans = 0;

  for (int i = 0; i < input.size(); ++i) {
    string s = input[i];
    if (s.empty()) {
      break;
    }
    vector<vector<long long>> seq;
    seq.push_back(signed_ints(input[i]));

    int row = 0;
    while (true) {
      bool allZeroes = true;
      seq.push_back(vector<long long>());
      for (int i = 1; i < seq[row].size(); ++i) {
        long long num = seq[row][i] - seq[row][i - 1];
        if (num != 0) {
          allZeroes = false;
        }
        seq[row + 1].push_back(num);
      }
      ++row;
      if (allZeroes) {
        break;
      }
    }
    seq[row].push_back(0);
    for (int i = row - 1; i >= 0; --i) {
      seq[i].push_back(seq[i + 1].back() + seq[i].back());
    }
    ans += seq[0].back();
  }

  return to_string(ans);
}

std::string y2023::solve_09b(const std::vector<std::string> &input) {
  long long ans = 0;

  for (int i = 0; i < input.size(); ++i) {
    string s = input[i];
    if (s.empty()) {
      break;
    }
    vector<vector<long long>> seq;
    seq.push_back(signed_ints(input[i]));

    int row = 0;
    while (true) {
      bool allZeroes = true;
      seq.push_back(vector<long long>());
      for (int i = 1; i < seq[row].size(); ++i) {
        long long num = seq[row][i] - seq[row][i - 1];
        if (num != 0) {
          allZeroes = false;
        }
        seq[row + 1].push_back(num);
      }
      ++row;
      if (allZeroes) {
        break;
      }
    }
    seq[row].push_back(0);
    for (int i = row - 1; i >= 0; --i) {
      seq[i].push_back(seq[i].front() - seq[i + 1].back());
    }
    ans += seq[0].back();
  }

  return to_string(ans);
}
