// Puzzle is available at https://adventofcode.com/2023/day/4
// Keywords:
#include "../../../src/utils.hpp"
#include "../2023.hpp"
using namespace std;

std::string y2023::solve_04a(const std::vector<std::string> &input) {
  int ans = 0;
  int n = input.size();
  for (int i = 0; i < n; ++i) {
    if (input[i].size() == 0) {
      break;
    }
    regex num(R"(([0-9]+))");

    int start = input[i].find(':');
    int fin = input[i].find('|');
    string win = input[i].substr(start, fin - start);
    string have = input[i].substr(fin);

    auto begin = std::sregex_iterator(win.begin(), win.end(), num);
    auto end = std::sregex_iterator();

    unordered_set<int> winning;
    vector<int> has;

    for (std::sregex_iterator it = begin; it != end; ++it) {
      smatch match = *it;
      int val = stoi(match[1].str());
      winning.insert(val);
    }

    begin = std::sregex_iterator(have.begin(), have.end(), num);
    for (std::sregex_iterator it = begin; it != end; ++it) {
      smatch match = *it;
      int val = stoi(match[1].str());
      has.push_back(val);
    }

    int local = 0;
    for (const auto &i : has) {
      if (winning.contains(i)) {
        if (!local) {
          local = 1;
        } else {
          local *= 2;
        }
      }
    }
    ans += local;
  }

  return to_string(ans);
}

std::string y2023::solve_04b(const std::vector<std::string> &input) {
  int ans = 0;
  int n = input.size();
  vector<int> cards(n, 1);
  for (int i = 0; i < n; ++i) {
    if (input[i].size() == 0) {
      break;
    }
    regex num(R"(([0-9]+))");

    int start = input[i].find(':');
    int fin = input[i].find('|');
    string win = input[i].substr(start, fin - start);
    string have = input[i].substr(fin);

    auto begin = std::sregex_iterator(win.begin(), win.end(), num);
    auto end = std::sregex_iterator();

    unordered_set<int> winning;
    vector<int> has;

    for (std::sregex_iterator it = begin; it != end; ++it) {
      smatch match = *it;
      int val = stoi(match[1].str());
      winning.insert(val);
    }

    begin = std::sregex_iterator(have.begin(), have.end(), num);
    for (std::sregex_iterator it = begin; it != end; ++it) {
      smatch match = *it;
      int val = stoi(match[1].str());
      has.push_back(val);
    }

    int local = 0;
    for (const auto &i : has) {
      if (winning.contains(i)) {
        local += 1;
      }
    }

    for (int j = i + 1; local > 0; ++j, --local) {
      cards[j] += cards[i];
    }
    ans += local;
  }

  for (int i = 0; i < cards.size(); ++i) {
    ans += cards[i];
  }

  return to_string(ans);
}
