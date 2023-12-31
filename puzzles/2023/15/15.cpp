// Puzzle is available at https://adventofcode.com/2023/day/15
// Keywords:
#include "../../../src/utils.hpp"
#include "../2023.hpp"
using namespace std;

int h(string &s) {
  int val = 0;
  for (const char c : s) {
    val += c;
    val *= 17;
    val %= 256;
  }
  return val;
}

std::string y2023::solve_15a(const std::vector<std::string> &input) {
  long long ans = 0;
  auto tokens = split(input[0]);
  for (auto &s : tokens) {
    ans += h(s);
  }
  return to_string(ans);
}

struct Lens {
  string label;
  int pos;
  int power;
};

int pos_in_box(vector<Lens> &box, string label) {
  for (int i = 0; i < box.size(); ++i) {
    if (box[i].label == label) {
      return i;
    }
  }
  return -1;
}

std::string y2023::solve_15b(const std::vector<std::string> &input) {
  long long ans = 0;
  size_t pos;
  auto tokens = split(input[0]);
  vector<vector<Lens>> boxes(256);
  for (auto &t : tokens) {
    int op;
    if (t.find('=') != string::npos) {
      pos = t.find('=');
      op = 0;  // add
    } else {
      pos = t.find('-');
      op = 1;  // delete
    }
    Lens l;
    l.label = t.substr(0, pos);
    if (op == 0) {
      l.power = stoi(t.substr(pos + 1));
    }

    int hash = h(l.label);

    int pb = pos_in_box(boxes[hash], l.label);
    if (op == 1) {
      if (pb == -1) {
        continue;
      }
      boxes[hash].erase(boxes[hash].begin() + pb);
    } else {
      if (pb == -1) {
        boxes[hash].push_back(l);
      } else {
        boxes[hash][pb] = l;
      }
    }
  }

  for (int i = 0; i < 256; ++i) {
    for (int j = 0; j < boxes[i].size(); ++j) {
      ans += (i + 1) * (j + 1) * boxes[i][j].power;
    }
  }

  return to_string(ans);
}