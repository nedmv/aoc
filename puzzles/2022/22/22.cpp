// Puzzle is available at https://adventofcode.com/2022/day/22
// Keywords:
#include "../../../src/utils.hpp"
#include "../2022.hpp"
using namespace std;

const vector<int> moves = {0, 1, 0, -1, 0};  // right - down - left - up

std::string y2022::solve_22a(const std::vector<std::string> &input) {
  string path;
  vector<string> m;
  for (int i = 0; i < input.size(); ++i) {
    if (input[i].empty()) {
      path = input[i + 1];
      break;
    }
    m.push_back(input[i]);
  }

  int rows = m.size();

  int cols = 0;
  for (const auto &p : m) {
    if (p.size() > cols) {
      cols = p.size();
    }
  }
  for (auto &p : m) {
    while (p.size() < cols) {
      p.push_back(' ');
    }
  }
  std::regex num(R"(([0-9]+))");
  auto begin = std::sregex_iterator(path.begin(), path.end(), num);
  auto end = std::sregex_iterator();

  std::vector<int> steps;

  for (std::sregex_iterator i = begin; i != end; ++i) {
    std::smatch match = *i;
    steps.push_back(stoi(match[1].str()));
  }
  regex letter(R"(([RL]))");
  begin = std::sregex_iterator(path.begin(), path.end(), letter);
  end = std::sregex_iterator();

  vector<char> letters;

  for (std::sregex_iterator i = begin; i != end; ++i) {
    std::smatch match = *i;
    letters.push_back(match[1].str()[0]);
  }

  int turn = 0;
  vector<int> pos = {0, 0, 0};
  while (m[pos[0]][pos[1]] != '.') {
    pos[1]++;
  }

  while (turn < steps.size()) {
    for (int i = 0; i < steps[turn]; ++i) {
      int row = pos[0];
      int col = pos[1];

      do {
        row = row + moves[pos[2]];
        col = col + moves[pos[2] + 1];

        if (row < 0) {
          row = rows - 1;
        }
        if (col < 0) {
          col = cols - 1;
        }
        if (row == rows) {
          row = 0;
        }
        if (col == cols) {
          col = 0;
        }
      } while (m[row][col] == ' ');
      if (m[row][col] == '#') {
        break;
      } else {
        pos[0] = row;
        pos[1] = col;
      }
    }
    if (turn < letters.size()) {
      if (letters[turn] == 'R') {
        pos[2] = (pos[2] + 1) % 4;
      } else {
        pos[2] = (pos[2] - 1) % 4;
        if (pos[2] < 0) {
          pos[2] += 4;
        }
      }
    }
    ++turn;
  }
  int pass = 1000 * (pos[0] + 1) + 4 * (pos[1] + 1) + pos[2];
  return to_string(pass);
}

vector<int> get_new_pos(vector<int> pos) {
  int row = pos[0] + moves[pos[2]];
  int col = pos[1] + moves[pos[2] + 1];
  int dir = pos[2];
  int cube = pos[3];

  if (row < 0 || col < 0 || row > 49 || col > 49) {
    switch (pos[3]) {
      case 0:
        if (row > 49) {
          cube = 2;
          row = 49;
          dir = 2;
          swap(row, col);
        } else if (row < 0) {
          cube = 5;
          row = 49;
        } else if (col > 49) {
          cube = 3;
          dir = 2;
          col = 49;
          row = 49 - row;
        } else if (col < 0) {
          cube = 1;
          col = 49;
        }
        break;

      case 1:
        if (col > 49) {
          cube = 0;
          col = 0;
        } else if (row > 49) {
          cube = 2;
          row = 0;
        } else if (col < 0) {
          cube = 4;
          dir = 0;
          col = 0;
          row = 49 - row;
        } else if (row < 0) {
          cube = 5;
          dir = 0;
          row = 0;
          swap(row, col);
        }
        break;

      case 2:
        if (row < 0) {
          cube = 1;
          row = 49;
        } else if (row > 49) {
          cube = 3;
          row = 0;
        } else if (col < 0) {
          cube = 4;
          col = 0;
          dir = 1;
          swap(row, col);
        } else if (col > 49) {
          cube = 0;
          dir = 3;
          col = 49;
          swap(row, col);
        }
        break;

      case 3:
        if (row < 0) {
          cube = 2;
          row = 49;
        } else if (col < 0) {
          cube = 4;
          col = 49;
        } else if (row > 49) {
          cube = 5;
          row = 49;
          dir = 2;
          swap(row, col);
        } else if (col > 49) {
          cube = 0;
          dir = 2;
          col = 49;
          row = 49 - row;
        }
        break;

      case 4:
        if (col > 49) {
          cube = 3;
          col = 0;
        } else if (row > 49) {
          cube = 5;
          row = 0;
        } else if (col < 0) {
          cube = 1;
          dir = 0;
          col = 0;
          row = 49 - row;
        } else if (row < 0) {
          cube = 2;
          dir = 0;
          row = 0;
          swap(row, col);
        }
        break;

      case 5:
        if (row < 0) {
          cube = 4;
          row = 49;
        } else if (row > 49) {
          cube = 0;
          row = 0;
        } else if (col < 0) {
          cube = 1;
          col = 0;
          dir = 1;
          swap(row, col);
        } else if (col > 49) {
          cube = 3;
          dir = 3;
          col = 49;
          swap(row, col);
        }
        break;

      default:
        cout << "Failed to recognise current cube!" << endl;
    }
  }
  return {row, col, dir, cube};
}

std::string y2022::solve_22b(const std::vector<std::string> &input) {
  string path;
  vector<string> m;
  for (int i = 0; i < input.size(); ++i) {
    if (input[i].empty()) {
      path = input[i + 1];
      break;
    }
    m.push_back(input[i]);
  }

  int rows = m.size();

  int cols = 0;
  for (const auto &p : m) {
    if (p.size() > cols) {
      cols = p.size();
    }
  }
  for (auto &p : m) {
    while (p.size() < cols) {
      p.push_back(' ');
    }
  }
  std::regex num(R"(([0-9]+))");
  auto begin = std::sregex_iterator(path.begin(), path.end(), num);
  auto end = std::sregex_iterator();

  std::vector<int> steps;

  for (std::sregex_iterator i = begin; i != end; ++i) {
    std::smatch match = *i;
    steps.push_back(stoi(match[1].str()));
  }

  regex letter(R"(([RL]))");
  begin = std::sregex_iterator(path.begin(), path.end(), letter);
  end = std::sregex_iterator();

  vector<char> letters;

  for (std::sregex_iterator i = begin; i != end; ++i) {
    std::smatch match = *i;
    letters.push_back(match[1].str()[0]);
  }

  const vector<vector<int>> cubes = {{0, 100},  {0, 50},  {50, 50},
                                     {100, 50}, {100, 0}, {150, 0}};

  int turn = 0;
  vector<int> pos = {0, 0, 0, 1};

  while (turn < steps.size()) {
    for (int i = 0; i < steps[turn]; ++i) {
      vector<int> new_pos = get_new_pos(pos);

      if (m[new_pos[0] + cubes[new_pos[3]][0]]
           [new_pos[1] + cubes[new_pos[3]][1]] == '#') {
        break;
      } else {
        pos = new_pos;
      }
    }
    if (turn < letters.size()) {
      if (letters[turn] == 'R') {
        pos[2] = (pos[2] + 1) % 4;
      } else {
        pos[2] = (pos[2] - 1) % 4;
        if (pos[2] < 0) {
          pos[2] += 4;
        }
      }
    }
    ++turn;
  }
  int pass = 1000 * (pos[0] + 1 + cubes[pos[3]][0]) +
             4 * (pos[1] + 1 + cubes[pos[3]][1]) + pos[2];
  return to_string(pass);
}
