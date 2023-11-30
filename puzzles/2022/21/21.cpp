// Puzzle is available at https://adventofcode.com/2022/day/21
// Keywords:
#include "../../../src/utils.hpp"
#include "../2022.hpp"
using namespace std;

#include <algorithm>
#include <atomic>
#include <cassert>
// #include <execution>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

struct Monkey2 {
  string name = "";
  string left = "";
  string right = "";
  char op = ' ';
  long long num = LLONG_MIN;
};

long long solve(unordered_map<string, Monkey2> &m, const string &name) {
  Monkey2 cur = m[name];
  char op = cur.op;

  if (long long num = cur.num; num != LLONG_MIN) return num;

  switch (op) {
    case '+':
      m[name].num = solve(m, cur.left) + solve(m, cur.right);
      break;
    case '-':
      m[name].num = solve(m, cur.left) - solve(m, cur.right);
      break;
    case '*':
      m[name].num = solve(m, cur.left) * solve(m, cur.right);
      break;
    case '/':
      m[name].num = solve(m, cur.left) / solve(m, cur.right);
      break;
    case '=':
      m[name].num = (solve(m, cur.left) == solve(m, cur.right));
    default:
      break;
  }
  return m[name].num;
}

void solve_down(unordered_map<string, Monkey2> &m, const string &name,
                long long val) {
  Monkey2 *cur = &m[name];

  cur->num = val;
  if (name == "humn") {
    return;
  }

  long long l = m[cur->left].num;
  long long r = m[cur->right].num;

  if (l == LLONG_MAX) {
    switch (cur->op) {
      case '+':
        solve_down(m, cur->left, val - r);
        break;
      case '-':
        solve_down(m, cur->left, val + r);
        break;
      case '*':
        solve_down(m, cur->left, val / r);
        break;
      case '/':
        solve_down(m, cur->left, val * r);
        break;
      default:
        break;
    }
  } else {
    switch (cur->op) {
      case '+':
        solve_down(m, cur->right, val - l);
        break;
      case '-':
        solve_down(m, cur->right, l - val);
        break;
      case '*':
        solve_down(m, cur->right, val / l);
        break;
      case '/':
        solve_down(m, cur->right, l / val);
        break;
      default:
        break;
    }
  }
}

long long solve3(unordered_map<string, Monkey2> &m, const string &name) {
  Monkey2 *cur = &m[name];

  if (cur->num != LLONG_MIN) return cur->num;

  long long l = solve3(m, cur->left);
  long long r = solve3(m, cur->right);

  if (name == "root") {
    if (l == LLONG_MAX) {
      solve_down(m, cur->left, r);
    } else {
      solve_down(m, cur->right, l);
    }
  }

  if (l == LLONG_MAX || r == LLONG_MAX) {
    cur->num = LLONG_MAX;
    return LLONG_MAX;
  }

  switch (cur->op) {
    case '+':
      cur->num = l + r;
      break;
    case '-':
      cur->num = l - r;
      break;
    case '*':
      cur->num = l * r;
      break;
    case '/':
      cur->num = l / r;
      break;
    case '=':
      cur->num = (l == r);
      break;
    default:
      break;
  }
  return cur->num;
}

std::string y2022::solve_21a(const std::vector<std::string> &input) {
  unordered_map<string, Monkey2> monkeys;
  for (long long i = 0; i < input.size(); ++i) {
    if (!input[i].empty()) {
      Monkey2 m;
      m.name = input[i].substr(0, 4);
      if (input[i][6] >= '0' && input[i][6] <= '9') {
        m.num = stoi(input[i].substr(6));
      } else {
        m.left = input[i].substr(6, 4);
        m.op = input[i][11];
        m.right = input[i].substr(13);
      }
      monkeys[m.name] = m;
    }
  }
  return to_string(solve(monkeys, "root"));
}

std::string y2022::solve_21b(const std::vector<std::string> &input) {
  unordered_map<string, Monkey2> monkeys;
  for (long long i = 0; i < input.size(); ++i) {
    if (!input[i].empty()) {
      Monkey2 m;
      m.name = input[i].substr(0, 4);

      if (input[i][6] >= '0' && input[i][6] <= '9') {
        if (m.name != "humn") {
          m.num = stoi(input[i].substr(6));
        } else {
          m.num = LLONG_MAX;
        }
      } else {
        m.left = input[i].substr(6, 4);
        if (m.name != "root") {
          m.op = input[i][11];
        } else {
          m.op = '=';
        }
        m.right = input[i].substr(13);
      }
      monkeys[m.name] = m;
    }
  }

  solve3(monkeys, "root");
  return to_string(monkeys["humn"].num);
}
