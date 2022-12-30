// Puzzle is available at https://adventofcode.com/2022/day/14
// Keywords:
#include "../../../src/utils.hpp"
#include "../2022.hpp"
using namespace std;

vector<vector<int>> parse_line(const string &s) {
  int pos = 0;
  vector<vector<int>> result;
  while (pos < s.size()) {
    vector<int> cur;
    int pos2 = s.find(',', pos);
    cur.push_back(stoi(s.substr(pos, pos2 - pos)));
    pos = pos2 + 1;
    pos2 = s.find(' ', pos);
    if (pos2 != -1) {
      cur.push_back(stoi(s.substr(pos, pos2 - pos)));
      pos = pos2 + 4;
    } else {
      cur.push_back(stoi(s.substr(pos)));
      pos = s.size();
    }
    result.push_back(cur);
  }
  return result;
}

vector<vector<char>> draw_lines(const std::vector<std::string> &input,
                                bool part2) {
  vector<vector<vector<int>>> lines;
  for (const auto &s : input) {
    lines.push_back(parse_line(s));
  }

  vector<vector<char>> field(400, vector<char>(800, '.'));
  for (int i = 0; i < lines.size(); ++i) {
    for (int j = 1; j < lines[i].size(); ++j) {
      int x_min = min(lines[i][j - 1][0], lines[i][j][0]);
      int x_max = max(lines[i][j - 1][0], lines[i][j][0]);
      int y_min = min(lines[i][j - 1][1], lines[i][j][1]);
      int y_max = max(lines[i][j - 1][1], lines[i][j][1]);

      int x = x_min;
      int y = y_min;
      while (x <= x_max && y <= y_max) {
        field[y][x] = '#';
        x += sign(x_max - x_min);
        y += sign(y_max - y_min);
      }
    }
  }

  if (part2) {
    int max_y = 0;
    for (int y = field.size() - 1; y >= 0; y--) {
      for (int x = 0; x < field[0].size(); x++) {
        if (field[y][x] == '#') {
          max_y = y;
          break;
        }
      }
      if (max_y > 0) {
        break;
      }
    }

    max_y += 2;
    for (int x = 0; x < field[0].size(); x++) {
      field[max_y][x] = '#';
    }
  }

  return field;
}

bool empty(const vector<vector<char>> &field, int y, int x) {
  return field[y][x] != '#' && field[y][x] != 'o';
}

int drop_sand_a(vector<vector<char>> &field) {
  int count = 0;
  int turn;

  while (true) {
    int sand_x = 500;
    int sand_y = 0;
    for (turn = 1; turn < 300; ++turn) {
      ++sand_y;
      if (empty(field, sand_y, sand_x)) {
        continue;
      } else if (empty(field, sand_y, sand_x - 1)) {
        --sand_x;
      } else if (empty(field, sand_y, sand_x + 1)) {
        ++sand_x;
      } else {
        field[sand_y - 1][sand_x] = 'o';
        ++count;
        break;
      }
    }
    if (turn == 300) {
      break;
    }
  }
  return count;
}

int drop_sand_b(vector<vector<char>> &field) {
  int count = 0;

  while (true) {
    int sand_x = 500;
    int sand_y = 0;
    for (int turn = 0; turn < 300; ++turn) {
      if (field[sand_y + 1][sand_x] != '#' &&
          field[sand_y + 1][sand_x] != 'o') {
        ++sand_y;
      } else if (field[sand_y + 1][sand_x - 1] != '#' &&
                 field[sand_y + 1][sand_x - 1] != 'o') {
        ++sand_y;
        --sand_x;
      } else if (field[sand_y + 1][sand_x + 1] != '#' &&
                 field[sand_y + 1][sand_x + 1] != 'o') {
        ++sand_y;
        ++sand_x;
      } else {
        ++count;
        field[sand_y][sand_x] = 'o';
        if (sand_x == 500 && sand_y == 0) {
          return count;
        } else {
          break;
        }
      }
    }
  }
  return count;
}

std::string y2022::solve_14a(const std::vector<std::string> &input) {
  auto field = draw_lines(input, false);
  return to_string(drop_sand_a(field));
}

std::string y2022::solve_14b(const std::vector<std::string> &input) {
  auto field = draw_lines(input, true);
  return to_string(drop_sand_b(field));
}
