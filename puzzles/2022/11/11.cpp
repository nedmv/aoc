// Puzzle is available at https://adventofcode.com/2022/day/11
// Keywords:
#include "../2022.hpp"
#include "../../../src/utils.hpp"
using namespace std;

struct Monkey {
  deque<long long> items;
  long long divisor;
  int num_true;
  int num_false;
  long long count;
  smatch ops;
  Monkey() = default;
  Monkey(Monkey &&) noexcept = default;
};

class MonkeyManager {
  long long limiter = 1;
  bool partA;
  vector<Monkey> monkeys;

 public:
  MonkeyManager(const vector<string> &input, bool isPartA): partA(isPartA) {
    for (int i = 0; i < input.size(); i += 7) {
      monkeys.push_back(parseMonkey(input, i));
    }
    if (!partA) {
      for (int i = 0; i < monkeys.size(); ++i) {
        limiter *= monkeys[i].divisor;
      }
    }
  }
  Monkey parseMonkey(const std::vector<std::string> &input, long long num) {
    Monkey monkey;
    string s = input[++num].substr(18);
    while (!s.empty()) {
      long long item = stoi(s.substr(0, 2));
      if (s.size() > 2) {
        s = s.substr(4);
      } else {
        s.clear();
      }
      monkey.items.push_back(item);
    }
    regex reg(R"(  Operation: new = ([a-z0-9]+) ([+*]) ([a-z0-9]+))");
    regex_match(input[++num], monkey.ops, reg);
    monkey.divisor = stoi(input[++num].substr(21));
    monkey.num_true = stoi(input[++num].substr(29));
    monkey.num_false = stoi(input[++num].substr(30));
    monkey.count = 0;
    return monkey;
  }
  void loop(int turns) {
    for (int turn = 0; turn < turns; ++turn) {
      for (auto &monkey: monkeys) {
        inspect(monkey);
      }
    }
  }
  long long countBusiness() {
    vector<long long> counts;
    for (const auto &monkey: monkeys) {
      counts.push_back(monkey.count);
    }
    sort(counts.rbegin(), counts.rend());
    return counts[0]*counts[1];
  }
  void inspect (Monkey &monkey) {
    while (!monkey.items.empty()) {
      ++monkey.count;
      auto item = monkey.items.front();
      monkey.items.pop_front();

      long long first = (monkey.ops[1] == "old") ? item : stoi(monkey.ops[1]);
      long long second = (monkey.ops[3] == "old") ? item : stoi(monkey.ops[3]);
      if (monkey.ops[2] == "*") {
        item = first * second;
      } else {
        item = first + second;
      }
      if (partA) {
        item /= 3;
      } else {
        item %= limiter;
      }
      if (item % monkey.divisor == 0) {
        monkeys[monkey.num_true].items.push_back(item);
      } else {
        monkeys[monkey.num_false].items.push_back(item);
      }
    }
  }
};

std::string y2022::solve_11a(const std::vector<std::string> &input) {
  MonkeyManager manager(input, true);
  manager.loop(20);
  return to_string(manager.countBusiness());
}

std::string y2022::solve_11b(const std::vector<std::string> &input) {
  MonkeyManager manager(input, false);
  manager.loop(10000);
  return to_string(manager.countBusiness());
}
